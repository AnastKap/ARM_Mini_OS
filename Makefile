AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CFLAGS = -mthumb -mcpu=cortex-m3 -g -c -O0


all: boot.s kernel.c peripherals interrupts context_switching process
	$(AS) -g boot.s -o boot.o
	$(CC) $(CFLAGS) kernel.c -o kernel.o
	$(LD) -T linker.ld -o kernel.elf boot.o kernel.o gpio.o interrupt.o context_switching.o process.o #The linker script is needed
	$(OBJCOPY) -O binary kernel.elf boot.bin
	

peripherals: peripherals/gpio.h peripherals/gpio.c
	$(CC) $(CFLAGS) peripherals/gpio.c -o gpio.o
	
interrupts: interrupts/interrupt.c interrupts/interrupt.h
	$(CC) $(CFLAGS) interrupts/interrupt.c -o interrupt.o
	
context_switching: context_switching/context_switching.c context_switching/context_switching.h
	$(CC) $(CFLAGS) context_switching/context_switching.c -o context_switching.o
	
process: process/process.c process/process.h
	$(CC) $(CFLAGS) process/process.c -o process.o



# Run * make flash * if you want to build the source and flash it
flash: all
	st-flash write boot.bin 0x8000000


# Run * make debug * if you want to build the source, flash it to the stm32 and debug it
debug: flash
	gdb-multiarch -x gdb_auto


# Run * make clean * if you want to remove all the additionally generated files and keep the source files only
clean:
	rm -f *.o *.elf *.bin
