
/*
*	
*	The Kernel
*	
*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "hal.h"

//halio
void hal_io_serial_init();
void hal_io_serial_putc(uint8_t, uint8_t);
uint8_t hal_io_serial_getc(uint8_t);

void delay(int32_t);


/*
 *		Kernel's entry point
 *
**/
void main(uint32_t r0, uint32_t r1, uint32_t atags){

	uint32_t mybuffer = hal_io_video_init();
	char o = 'o';
	char s = 's';
	uint32_t colour = 0x5A9C;
	hal_io_video_putc(mybuffer, 100, 175, colour, o);
	hal_io_video_putc(mybuffer, 279, 175, colour, o);
	hal_io_video_putc(mybuffer, 409, 175, colour, s);

	//Begin the one-line typewriter
	hal_io_serial_putc('a', 'W');
	hal_io_serial_putc('a', 'E');
	hal_io_serial_putc('a', 'L');
	hal_io_serial_putc('a', 'C');
	hal_io_serial_putc('a', 'O');
	hal_io_serial_putc('a', 'M');
	hal_io_serial_putc('a', 'E');
	hal_io_serial_putc('a', ' ');
	hal_io_serial_putc('a', 'T');
	hal_io_serial_putc('a', 'O');
	hal_io_serial_putc('a', ' ');
	hal_io_serial_putc('a','O');
	hal_io_serial_putc('a',' ');
	hal_io_serial_putc('a','O');
	hal_io_serial_putc('a','S');
	hal_io_serial_putc('a','\n');
	hal_io_serial_putc('a','\r');

	while (1)
		hal_io_serial_putc('a',hal_io_serial_getc('a'));// <<---- This is why your CPU goes crazy when you run the kernel
}