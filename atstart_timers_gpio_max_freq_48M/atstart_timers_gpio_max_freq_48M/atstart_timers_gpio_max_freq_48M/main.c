#include <atmel_start.h>

int status = false;


struct timer_task task;

static void cbf ( const struct timer_task *const timer_task )
{
	REG_PORT_OUTSET0 = PORT_PA19;
	REG_PORT_OUTCLR0 = PORT_PA19;
}



int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	task.interval	= 1;
	task.cb			= cbf;
	task.mode		= TIMER_TASK_REPEAT;
	
	timer_add_task( &TIMER_0, &task );
	
	timer_start( &TIMER_0 );
	
	for ( ;; )
	{
		
	}
	
	
}

/*
*	Reaches up to 3MHz frequency, therefore the GPIO is not the bottleneck
*/

//int main(void)
//{
	///* Initializes MCU, drivers and middleware */
	//atmel_start_init();
//
	///* Replace with your application code */
	//for ( ;; )
	//{
		//REG_PORT_OUTSET0 = PORT_PA19;
		//REG_PORT_OUTCLR0 = PORT_PA19;
	//}
//}
