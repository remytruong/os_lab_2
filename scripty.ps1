arm-none-eabi-as src\hal_io_video.s -o output\hal_io_video.o
arm-none-eabi-gcc -mcpu=arm6 -fpic  -ffreestanding -std=gnu99 -c C:\Users\remtr\Desktop\kernel\src\hal.c -o C:\Users\remtr\Desktop\kernel\output\hal.o  -O0
arm-none-eabi-gcc -mcpu=arm6 -fpic  -ffreestanding -std=gnu99 -c C:\Users\remtr\Desktop\kernel\src\kernel.c -o C:\Users\remtr\Desktop\kernel\output\kernel.o  -O0
arm-none-eabi-ld C:\Users\remtr\Desktop\kernel\output\boot.o C:\Users\remtr\Desktop\kernel\output\hal_io_video.o C:\Users\remtr\Desktop\kernel\output\hal.o C:\Users\remtr\Desktop\kernel\output\video.o C:\Users\remtr\Desktop\kernel\output\kernel.o -T C:\Users\remtr\Desktop\kernel\output\linker.ld -o C:\Users\remtr\Desktop\kernel\output\kernel.elf
 & 'C:\Program Files\qemu\qemu-system-arm.exe' -m 256 -M raspi2 -serial stdio -kernel C:\Users\remtr\Desktop\kernel\output\kernel.elf