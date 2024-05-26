#ifndef USB_SERIAL_H_
#define USB_SERIAL_H_

#include <string.h>
#include <atmel_start.h>

#include "cdcdf_acm.h"
#include "cdcdf_acm_desc.h"

void usb_serial_init( void );

unsigned int usb_serial_get_available_bytes( void );

unsigned int usb_serial_str_present( void );

int usb_serial_read( uint8_t * const destination, const unsigned int size );

void usb_serial_write( const uint8_t * const buffer, const unsigned int size );

void usb_serial_puts( const uint8_t * const str );

int usb_serial_gets( uint8_t *const destination, const uint8_t size );

int usb_serial_getles( uint8_t *const destination, const uint8_t size );

void usb_serial_clear( void );

// TODO usb_serial_printf







#endif /* USB_SERIAL_H_ */