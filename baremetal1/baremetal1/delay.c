/*
 * delay.c
 *
 * Created: 22/12/2022 22:31:21
 *  Author: Abdurrahman
 */ 

#include "delay.h"

void delay_n_cycles( unsigned long n )
{
	__asm (
	"loop: DMB	\n"
	"SUB r0, r0, #1 \n"
	"CMP r0, #0  \n"
	"BNE loop         "
	);
} // delay_n_cycles()
