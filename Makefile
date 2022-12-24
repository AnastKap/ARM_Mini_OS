AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CFLAGS = -mthumb -mcpu=cortex-m3 -g -c -O0


all: boot.s kernel.c gpio.o interrupt.o context_switching.o process.o memory.o
	$(AS) -g boot.s -o boot.o
	$(CC) $(CFLAGS) kernel.c -o kernel.o
	$(LD) -T linker.ld -o kernel.elf boot.o kernel.o gpio.o interrupt.o context_switching.o process.o memory.o #The linker script is needed
	$(OBJCOPY) -O binary kernel.elf boot.bin
	make clean_obj


gpio.o: peripherals/gpio.h peripherals/gpio.c
	$(CC) $(CFLAGS) peripherals/gpio.c -o gpio.o

interrupt.o: interrupts/interrupt.c interrupts/interrupt.h
	$(CC) $(CFLAGS) interrupts/interrupt.c -o interrupt.o

context_switching.o: context_switching/context_switching.c context_switching/context_switching.h
	$(CC) $(CFLAGS) context_switching/context_switching.c -o context_switching.o

process.o: process/process.c process/process.h
	$(CC) $(CFLAGS) process/process.c -o process.o

memory.o: memory_management/memory.c memory_management/memory.c
	$(CC) $(CFLAGS) memory_management/memory.c -o memory.o



# Run * make flash * if you want to build the source and flash it
flash: all
	st-flash write boot.bin 0x8000000


# Run * make debug * if you want to build the source, flash it to the stm32 and debug it
debug: flash
	gdb-multiarch -x gdb_auto


# Run * make clean * if you want to remove all the additionally generated files and keep the source files only
clean:
	rm -f *.o *.elf *.bin


clean_obj:
	rm -f *.o


disasm:
	arm-none-eabi-objdump -D kernel.elf > disassembly.txt
	vim disassembly.txt
