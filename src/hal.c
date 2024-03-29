#include <stddef.h>
#include <stdint.h>
#include "hal.h"

int32_t _hal_io_video(void);

void _hal_io_video_putpixel(uint32_t framebuffer, int pixel, uint32_t colour);

/*
*	From
*	https://wiki.osdev.org/Raspberry_Pi_Bare_Bones#Building_a_Cross-Compiler
*
*/
void delay(int32_t count) {
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
    : "=r"(count): [count]"0"(count) : "cc");
}

void memory_write(uint32_t address, uint32_t v){
    *(volatile uint32_t*)address = v;
}

uint32_t memory_read(uint32_t address){
    return *(volatile uint32_t*)address;
}

int32_t hal_io_video_init() {
    return _hal_io_video();
}
void hal_io_video_putpixel(uint32_t framebuffer,int x, int y, uint32_t colour) {
    _hal_io_video_putpixel(framebuffer, (y * 640 + x) * 2, colour);
}

void hal_io_video_putc(uint32_t framebuffer, int x, int y, uint32_t colour, char character) {
	int current_x_offset = x;
	int current_y_offset = y;
	switch (character) {
		case 'o':
			hal_io_video_draw_horiz_line(framebuffer, x, y, 100, colour);
			hal_io_video_draw_horiz_line(framebuffer, x, y+99, 100, colour);
			hal_io_video_draw_vert_line(framebuffer, x, y, 100, colour);
			hal_io_video_draw_vert_line(framebuffer, x + 100, y, 100, colour);
			break;
		case 's':
			hal_io_video_draw_horiz_line(framebuffer, x, y, 100, colour);
			hal_io_video_draw_horiz_line(framebuffer, x, y + 49, 100, colour);
			hal_io_video_draw_vert_line(framebuffer, x, y, 50, colour);
			hal_io_video_draw_vert_line(framebuffer, x + 100, y + 50, 50, colour);
			hal_io_video_draw_horiz_line(framebuffer, x, y + 99, 100, colour);
	}
}

void hal_io_video_draw_horiz_line(uint32_t framebuffer, int x, int y, int length, uint32_t colour) {
	for (int i = 0; i < length; i++) {
		hal_io_video_putpixel(framebuffer, x+i, y, colour);
		hal_io_video_putpixel(framebuffer, x+i, y+1, colour);
		hal_io_video_putpixel(framebuffer, x+i, y+2, colour);
	}
}

void hal_io_video_draw_vert_line(uint32_t framebuffer, int x, int y, int length, uint32_t colour) {
	for (int i = 0; i < length; i++) {
		hal_io_video_putpixel(framebuffer, x, y + i, colour);
		hal_io_video_putpixel(framebuffer, x + 1, y + i, colour);
		hal_io_video_putpixel(framebuffer, x + 2, y + i, colour);
	}
}

void hal_io_serial_init() {
    // Disable UART0.
    memory_write(UART0_CR, 0x00000000);
    // Setup the GPIO pin 14 && 15.

    // Disable pull up/down for all GPIO pins & delay for 150 cycles.
    memory_write(GPPUD, 0x00000000);
    delay(150);

    // Disable pull up/down for pin 14,15 & delay for 150 cycles.
    memory_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);

    // Write 0 to GPPUDCLK0 to make it take effect.
    memory_write(GPPUDCLK0, 0x00000000);

    // Clear pending interrupts.
    memory_write(UART0_ICR, 0x7FF);

    // Set integer & fractional part of baud rate.
    // Divider = UART_CLOCK/(16 * Baud)
    // Fraction part register = (Fractional part * 64) + 0.5
    // UART_CLOCK = 3000000; Baud = 115200.

    // Divider = 3000000 / (16 * 115200) = 1.627 = ~1.
    memory_write(UART0_IBRD, 1);
    // Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
    memory_write(UART0_FBRD, 40);

    // Enable FIFO & 8 bit data transmissio (1 stop bit, no parity).
    memory_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    // Mask all interrupts.
    memory_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
                             (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    // Enable UART0, receive & transfer part of UART.
    memory_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void hal_io_serial_putc(uint8_t serial_id, uint8_t c) {
    switch (serial_id) {
        case 'a' :
            //wait for it to be ready
            while ( memory_read(UART0_FR) & (1 << 5) );

            //write
            memory_write(UART0_DR, c);
            break;
        default:
            //wait for it to be ready
            while ( memory_read(UART0_FR) & (1 << 5) );

            //write
            memory_write(UART0_DR, c);
    }
}

uint8_t hal_io_serial_getc(uint8_t serial_id) {
    switch (serial_id) {
        case 'a' :
            //wait for it to be ready
            while ( memory_read(UART0_FR) & (1 << 4) );

            //write
            return memory_read(UART0_DR);
        default:
            //wait for it to be ready
            while ( memory_read(UART0_FR) & (1 << 4) );

            //write
            return memory_read(UART0_DR);
    }
}