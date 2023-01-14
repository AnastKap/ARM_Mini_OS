AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CFLAGS = -mthumb -mcpu=cortex-m3 -g -c -O0 -Wall -Wno-builtin-declaration-mismatch # The last flag is in order to avoid warning for malloc() which is built-in
LOG = "log.txt"

all:
	@echo "\033[93mBuilding the source files...\033[39m"
	@make build > $(LOG)
	@echo "\033[93mBinary file is ready!\033[39m"

build: boot.s kernel.c gpio.o interrupt.o context_switching.o process.o memory.o clock.o adc.o usart.o
	$(AS) -g boot.s -o boot.o
	$(CC) $(CFLAGS) kernel.c -o kernel.o
	@echo "------ Linking everything and building the bin file! ------"
	$(LD) -T linker.ld -o kernel.elf boot.o kernel.o gpio.o interrupt.o context_switching.o process.o memory.o clock.o adc.o usart.o #The linker script is needed
	$(OBJCOPY) -O binary kernel.elf boot.bin
	@echo "-----------------------------------------------------------"
	make clean_obj
	make disasm


gpio.o: peripherals/gpio.h peripherals/gpio.c
	$(CC) $(CFLAGS) peripherals/gpio.c -o gpio.o

interrupt.o: interrupts/interrupt.c interrupts/interrupt.h
	$(CC) $(CFLAGS) interrupts/interrupt.c -o interrupt.o

context_switching.o: context_switching/context_switching.c context_switching/context_switching.h
	$(CC) $(CFLAGS) context_switching/context_switching.c -o context_switching.o

process.o: process/process.c process/process.h
	$(CC) $(CFLAGS) process/process.c -o process.o

memory.o: memory_management/memory.c memory_management/memory.h
	$(CC) $(CFLAGS) memory_management/memory.c -o memory.o

clock.o: clock/clock.c clock/clock.h
	$(CC) $(CFLAGS) clock/clock.c -o clock.o

adc.o: peripherals/adc.h peripherals/adc.c
	$(CC) $(CFLAGS) peripherals/adc.c -o adc.o

timer.o: peripherals/timer.h peripherals/timer.c
	$(CC) $(CFLAGS) peripherals/timer.c -o timer.o

usart.o: peripherals/usart.h peripherals/usart.c
	$(CC) $(CFLAGS) peripherals/usart.c -o usart.o



# Run * make flash * if you want to build the source and flash it
flash: all
	@echo "\033[93mFlashing the STM32...\033[39m"
	@st-flash write boot.bin 0x8000000
	@echo "\033[93mFlashed the device successfully!\033[39m"


# Run * make debug * if you want to build the source, flash it to the stm32 and debug it
debug: flash
	@echo "\033[93mStarting the debugging session...\033[39m"
	@echo "------ Enabling debugger communication... ------" >> $(LOG)
	openocd -f /usr/local/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/local/share/openocd/scripts/board/stm32f103c8_blue_pill.cfg &
	@gdb-multiarch -x gdb_auto
	@pkill openocd
	@echo "\033[93mDebugging session ended.\033[39m"


# Run * make clean * if you want to remove all the additionally generated files and keep the source files only
clean:
	rm -f *.o *.elf *.bin
	rm -f $(LOG)
	rm -f disassembly.txt


clean_obj:
	rm -f *.o


disasm:
	arm-none-eabi-objdump -D kernel.elf > disassembly.txt
