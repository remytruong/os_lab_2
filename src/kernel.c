
/*
*	
*	The Kernel
*	
*/

#include <stddef.h>
#include <stdint.h>
#include "hal.h"

//halio
void hal_io_serial_init();
void hal_io_serial_putc(uint8_t, uint8_t);
uint8_t hal_io_serial_getc(uint8_t);

void delay(int32_t);
void _hal_io_video(void);


/*
 *		Kernel's entry point
 *
**/
void main(uint32_t r0, uint32_t r1, uint32_t atags){
	
	int32 mybuffer= hal_io_video_init();
	//Begin the one-line typewriter
	hal_io_serial_putc('a','y');
	hal_io_serial_putc('a','e');
	hal_io_serial_putc('a','e');
	hal_io_serial_putc('a','t');
	hal_io_serial_putc('a','\n');
	hal_io_serial_putc('a','\r');

	while (1)
		hal_io_serial_putc('a',hal_io_serial_getc('a'));// <<---- This is why your CPU goes crazy when you run the kernel
}