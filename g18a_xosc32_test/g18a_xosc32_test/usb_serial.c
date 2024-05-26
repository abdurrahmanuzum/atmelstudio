#include <string.h>
#include "atmel_start.h"
#include "usb_serial.h"


#if CONF_USBD_HS_SP
static uint8_t single_desc_bytes[] = {
/* Device descriptors and Configuration descriptors list. */
CDCD_ACM_HS_DESCES_LS_FS};
static uint8_t single_desc_bytes_hs[] = {
/* Device descriptors and Configuration descriptors list. */
CDCD_ACM_HS_DESCES_HS};
#define USBD_CDC_BUFFER_SIZE CONF_USB_CDCD_ACM_DATA_BULKIN_MAXPKSZ_HS
#else
static uint8_t single_desc_bytes[] = {
/* Device descriptors and Configuration descriptors list. */
CDCD_ACM_DESCES_LS_FS};
#define USBD_CDC_BUFFER_SIZE CONF_USB_CDCD_ACM_DATA_BULKIN_MAXPKSZ
#endif

static struct usbd_descriptors single_desc[]
= {{single_desc_bytes, single_desc_bytes + sizeof(single_desc_bytes)}
#if CONF_USBD_HS_SP
,
{single_desc_bytes_hs, single_desc_bytes_hs + sizeof(single_desc_bytes_hs)}
#endif
};


#ifndef INPUT_BUFFER_SIZE
#define INPUT_BUFFER_SIZE USBD_CDC_BUFFER_SIZE
#endif

#ifndef	OUTPUT_BUFFER_SIZE
#define OUTPUT_BUFFER_SIZE USBD_CDC_BUFFER_SIZE
#endif

#if		INPUT_BUFFER_SIZE < USBD_CDC_BUFFER_SIZE
#define INPUT_BUFFER_SIZE USBD_CDC_BUFFER_SIZE
#endif


// Ctrl endpoint buffer
static uint8_t ctrl_buffer[64];

// Private input/output buffer
static uint8_t usbd_cdc_buffer[ USBD_CDC_BUFFER_SIZE ] __attribute__(( aligned(4) ));
/*
* Note:
* Auto-generated example code does opaque stuff to
* ensure 4 bit alignment of this array. Might as well
* do it explicitly.
*
* Example code : uint32_t buffer [ SIZE / 4 ]; (not real var. names)
* which then consequently requires typecasts, as all functions 
* expect uint8_t.
*/

/*
 * Intermediate buffers between driver buffer and user-side
 * read/write functions. For a better practice, these
 * should have been circular buffers, they will be 
 * converted soon. 
 */
static volatile uint8_t input_buffer	[ INPUT_BUFFER_SIZE ];
static volatile uint8_t output_buffer	[ OUTPUT_BUFFER_SIZE ];

/*
 * Dynamic size of pending read/write buffers.
 * Contains the bits that have been read from the device
 * but have not yet been requested by user, or pushed by
 * user to be written, but have not yet been done so.
 */
static volatile unsigned int input_length  = 0;
static volatile unsigned int output_length = 0;

/*
 * Status flags
 */
static volatile bool pending_read		= 0;
static volatile bool pending_write		= 0;
static volatile bool usbd_cdc_connected	= 0;



/*
 * Starts the reading process, sets the respective flag
 * when the reading is done, respective callback function is called.
 */
static int32_t usbd_cdc_read_start()
{
    pending_read = true;
    return cdcdf_acm_read(usbd_cdc_buffer, USBD_CDC_BUFFER_SIZE);
}



/*
 * Callback function signaling that a read operation is complete.
 * Copies the results into the private buffer, clears the respective flag
 * and starts another read process.
 * Another read process must be triggered, as otherwise if the host device attempts 
 * to send more data, it would "apparently" freeze.
 */
static bool usbd_cdc_read_finished( const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count )
{
	bool result = false;

	// Check if the read is completed successfully
	if ( rc != USB_XFER_DONE )
	{
		// error
		result = true;
	}
	else if ( count > 0 ) // count is the bytes available to be read.
	{
		// Input buffer may be partially full. Calculate the available space
		unsigned int available_size = INPUT_BUFFER_SIZE - input_length;
		
		// If the incoming data cannot fit the available space in input buffer
		if ( count > available_size )
		{
			/* 
			 * Note:
			 * If the host program crashes, this is probably where it happens.
			 *
			 * This situation is likely to halt the host trying to send data 
			 * until the receiving device clears its input buffers and is 
			 * ready to accept more data, or presumably host device runs 
			 * into a timeout and quits.
			 *
			 * for better practice, a timeout callback can be added in order 
			 * to clear input buffers after a certain amount of time has 
			 * been passed.
			 */
			
			// error
			result = true;
		}
		else
		{
			// append the incoming data to input buffer
			memcpy( &input_buffer[input_length], usbd_cdc_buffer, count );
			input_length += count;

			// prepare for next read cycle
			pending_read = false;
			memset( usbd_cdc_buffer, 0, USBD_CDC_BUFFER_SIZE );
		}

	}

	// start next read cycle
	usbd_cdc_read_start();
	return result;
}



/*
 * Callback function signaling that a write operation is completed, simply clears the respective flag.
 */ 
static bool usbd_cdc_write_finished(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	// set the respective flag
    pending_write = false;
	
	// success
	return false;
}



/*
 * Starts the write operation. If the source data is larger than usbd_cdc buffer, 
 * it will be written in multiple consequent write cycles. (Iterative)
 */
static int32_t usbd_cdc_write_start( const uint8_t * const buffer, const unsigned int size )
{
	// if connected ?
	
	// Amount of bytes to write per write operation. There can be multiple
	// consequent write operations to fully write requested data.
	unsigned int bytes_to_write = size;
	
	// Amount of bytes left to be written. write cycles will run
	// until there is nothing left to be written.
	unsigned int bytes_left = size;
	
	// continue until everything has been written or connection is lost.
	while ( bytes_to_write > 0 && usbd_cdc_connected )
	{
		// set pending write flag to indicate a write operation has been started
		pending_write = true;
		
		// calculate if the source size exceeds buffer size
		bytes_to_write = bytes_left > USBD_CDC_BUFFER_SIZE ? USBD_CDC_BUFFER_SIZE : bytes_left;
		
		// copy the source buffer. Passing const buffers to the cdcdf_acm_write causes
		// write operation to never return for whatever reason...
		memcpy( output_buffer, buffer, bytes_to_write );
		
		cdcdf_acm_write( output_buffer, bytes_to_write );
		
		// wait until the write operation is completed
		while( pending_write && usbd_cdc_connected );
		
		// clear the output buffer
		memset( output_buffer, 0, OUTPUT_BUFFER_SIZE );
		
		// recalculate how many bytes are waiting to be written
		bytes_left -= bytes_to_write;		
	}

	// more appropriate error checking should be used here.
	return false;
}



/*
 * Callback in case of connection state change. 
 */
static bool usbd_cdc_state_changed( usb_cdc_control_signal_t state )
{
	if ( state.rs232.DTR ) // data terminal ready
	{
		/* Callbacks must be registered after endpoint allocation */
		cdcdf_acm_register_callback( CDCDF_ACM_CB_READ, (FUNC_PTR)usbd_cdc_read_finished );
		cdcdf_acm_register_callback( CDCDF_ACM_CB_WRITE, (FUNC_PTR)usbd_cdc_write_finished );

		usbd_cdc_connected = true;
		
		usbd_cdc_read_start();
	}
	else
	{
		usbd_cdc_connected = false;
	}

	/* No error. */
	return false;
}



// API frontend functions //



void usb_serial_init( void )
{
	/* usb stack init */
	usbdc_init(ctrl_buffer);

	/* usbdc_register_funcion inside */
	cdcdf_acm_init();

	usbdc_start(single_desc);
	usbdc_attach();

	// Initialize buffers with 0
	memset( usbd_cdc_buffer, 0, USBD_CDC_BUFFER_SIZE );
	memset( input_buffer,	 0, INPUT_BUFFER_SIZE	 );
	memset( output_buffer,	 0, OUTPUT_BUFFER_SIZE	 );

	// Wait for "cdc acm to be installed"
	// Add a timeout here. 
	// BLOCKS INTERRUPTS AS WELL
	while ( !cdcdf_acm_is_enabled() )
	{
		;
	}
	delay_ms(1000);

	cdcdf_acm_register_callback( CDCDF_ACM_CB_STATE_C, (FUNC_PTR)usbd_cdc_state_changed );
}



/*
 * Returns number of bytes ready to be read in the input buffer.
 */
unsigned int usb_serial_get_available_bytes( void )
{
    return input_length;
}



unsigned int usb_serial_str_present( void )
{
	char *cr = strchr( input_buffer, '\r' );
	char *nl = strchr( input_buffer, '\n' );
	
	// if no line termination present: no bytes to read, return 0
	if ( cr == NULL && nl == NULL ) 
	{
		return 0;
	}
	// if cr is present, return #of bytes until cr
	else if ( cr != NULL )
	{
		return (unsigned int)( cr - (char*)input_buffer );
	}
	// if cr is not present, and nl is present, return #of bytes until nl
	else if ( nl != NULL )
	{
		return (unsigned int)( nl - (char*)input_buffer );
	}
}



/*
 * Copies the requested size from input buffer to provided destination,
 * shifts the input buffer by the read amount. This is a destructive
 * function, what has been read is deleted from the input buffer.
 */
int usb_serial_read( uint8_t *destination, const unsigned int size )
{
	if ( input_length == 0 )
	{
		// nothing to read
		return 0;
	}


	// calculate if desired size exceeds the size of available data
	unsigned int bytes_to_read = size > input_length ? input_length : size;


	// transfer data to the destination
	memcpy( destination, input_buffer, bytes_to_read );

	// shift leftover data to the start of the array, and clear the remaining bytes
	memmove( input_buffer, &input_buffer[bytes_to_read], input_length - bytes_to_read ); //memcpy causes UB when src and dest overlaps!
	memset( &input_buffer[bytes_to_read], 0, INPUT_BUFFER_SIZE - bytes_to_read );
	
	input_length -= bytes_to_read;

	return bytes_to_read;
}



/*
 * Write an arbitrary array of characters with set size
 */
void usb_serial_write( const uint8_t * const buffer, const unsigned int size )
{
	usbd_cdc_write_start( buffer, size );
}



/*
 * Clears the input buffer
 */
void usb_serial_clear( void )
{
	memset( input_buffer, 0, INPUT_BUFFER_SIZE );
}



/*
 * Put String
 * Write a null-terminated C string.
 */
void usb_serial_puts( const uint8_t * const str )
{
	usbd_cdc_write_start( str, strlen( str ) );
}



/*
 * Get String
 * Temporary quick fix.
 */
// TODO: Properly implement this.
int usb_serial_gets( uint8_t *const destination, const uint8_t size )
{
	return usb_serial_getles( destination, size );
}



/*
 * Get Line Ended String.
 * Copies strings ended with \n or \r\n to destination. Returns bytes copied.
 * Does nothing and returns 0 if no line ending is found.
 */
int usb_serial_getles( uint8_t *const destination, const uint8_t size )
{
	// determine end of line 
	// look for carriage return
	char *line_end = strchr( input_buffer, '\r' );
	if ( line_end == NULL )
	{
		// look for line feed if cannot find carriage return
		line_end = strchr( input_buffer, '\n' );
		if ( line_end == NULL )
		{
			// nothing to read if neither is present
			return 0;
		}
	}
		
	// calculate length of the string that ends with \r\n or \n
	ptrdiff_t bytes_to_copy = line_end - (char*)input_buffer + 1;
		
	// will truncate if the string is too long
	if ( bytes_to_copy > size )
	{
		bytes_to_copy = size; 
	}
		
	// copy to destination and null-terminate
	memcpy( destination, input_buffer, bytes_to_copy );
	destination[ bytes_to_copy - 1 ] = '\0';
		

	// re-oder input buffer //

	// Find the next alphanumeric character in the input buffer
	int next_char_idx = bytes_to_copy - 1; // -1 because next_char_idx is an array index and not size
	for ( next_char_idx; next_char_idx < input_length; next_char_idx++ )
	{
		if ( isalnum( input_buffer[next_char_idx] ) )
		{
			break;
		}
	}
	
	// shift the contents of input buffer
	memmove( input_buffer, &input_buffer[next_char_idx], INPUT_BUFFER_SIZE - next_char_idx + 1 );
	memset( &input_buffer[ next_char_idx+1 ], 0, INPUT_BUFFER_SIZE - next_char_idx - 1 );
	
	// update the input length
	input_length -= next_char_idx;
	
	return bytes_to_copy;	
}
/*
 * I feel like there is "some" problem with the indexes, sizes and all the +1 and -1. 
 */


// teststring\r\n\0 000000...
// teststring\r\n\0 000000...
// i: -------^
// teststring\r\n\0 000000...
// i: ----------^
// teststring\r\n\0 000000...
// i: ------------^
// teststring\r\n\0 000000...
// i: --------------^
// 000000...

// teststring\r\n\0 next\r\n\0 0000...
// teststring\r\n\0 next\r\n\0 0000...
// i: -------^
// teststring\r\n\0 next\r\n\0 0000...
// i: ----------^
// teststring\r\n\0 next\r\n\0 0000...
// i: ------------^
// teststring\r\n\0 next\r\n\0 0000...
// i: --------------^
// next\r\n\0 0000...



///*
 //* fgets-ish
 //*/
//int usb_serial_gets( uint8_t *const destination, const uint8_t size )
//{
	//uint8_t bytes_to_read = size > input_length ? input_length : size;
	//
	//int i = 0;
	//uint8_t c = 0;
		//
	//// copy until cr, lf or \0
	//for ( i=0; i < bytes_to_read; i++, c = input_buffer[i] )
	//{
		//if ( c == '\n' || c == '\r' || c == '\0' )
		//{
			//break;
		//}
		//
		//destination[i] = c;
	//}
	//// null terminate destination string
	//destination[i] = '\0';
	//
	//// find next non-whitespace character to discard leading whitespaces
	//for ( i; (i < input_length) && isspace(c) && (c != '\0'); i++ )
	//{
		//c = input_buffer[i];
	//}
	//if ( c == '\0' && i < input_length ) { i++; }
	//
	//// shift the contents
	//memcpy( input_buffer, &input_buffer[i], i );
	//memset( &input_buffer[i], 0, INPUT_BUFFER_SIZE - i );
	//
	//return bytes_to_read;	
//}


