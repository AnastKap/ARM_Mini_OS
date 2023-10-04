# User definitions
STARTUP_FILE = src/boot.s
C_SRC_FILES = src/kernel.c src/*/*.c
BUILD_FOLDER = build


# Derived definitions
SRC_FILES = $(wildcard $(STARTUP_FILE) $(C_SRC_FILES))
OBJECT_FILES = $(foreach file, $(SRC_FILES), $(BUILD_FOLDER)/objs/$(subst src/,,$(file)))
OBJECT_FILES := $(foreach file, $(OBJECT_FILES), $(subst .c,.o,$(file)))	# .c file extension to .o
OBJECT_FILES := $(foreach file, $(OBJECT_FILES), $(subst .s,.o,$(file)))	# .s file extension to .o


# Global definitions
MAKE = make --no-print-directory
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CFLAGS = -mthumb -mcpu=cortex-m3 -g -c -O0 -Wall -Wno-builtin-declaration-mismatch # The last flag is in order to avoid warning for malloc() which is built-in

all:
	@$(MAKE) build
	@echo "\033[93mBinary file is ready!\033[39m"

prebuild:
	@mkdir -p $(BUILD_FOLDER)
	@mkdir -p $(BUILD_FOLDER)/objs
	@mkdir -p $(BUILD_FOLDER)/out
	$(foreach dir,$(shell cd src && ls -d */),$(shell mkdir -p $(BUILD_FOLDER)/objs/$(dir)))

build: prebuild $(OBJECT_FILES)
	@echo "\033[93mBuilding the source files...\033[39m"
	@echo "------ Linking everything and building the bin file! ------"
	@$(LD) -T linker.ld -o $(BUILD_FOLDER)/out/kernel.elf $(OBJECT_FILES) #The linker script is needed
	@$(OBJCOPY) -O binary $(BUILD_FOLDER)/out/kernel.elf $(BUILD_FOLDER)/out/boot.bin
	@echo "-----------------------------------------------------------"
	@$(MAKE) disasm


# File compilation
$(OBJECT_FILES): %.o: $(subst $(BUILD_FOLDER)/objs/,,$(wildcard %.o))
	$(eval STRIPPED = $(subst $(BUILD_FOLDER)/objs/,,$@))
	$(eval SRC_FILE_PREFIX = $(subst .o,,$(STRIPPED)))
	@if [ -f "src/$(SRC_FILE_PREFIX).s" ]; then \
		$(AS) -g src/$(SRC_FILE_PREFIX).s -o $@; \
	else \
		$(CC) $(CFLAGS) src/$(SRC_FILE_PREFIX).c -o $@; \
	fi


# Run * make flash * if you want to build the source and flash it
flash: all
	@echo "\033[93mFlashing the STM32...\033[39m"
	@st-flash write boot.bin 0x8000000
	@echo "\033[93mFlashed the device successfully!\033[39m"


# Run * make debug * if you want to build the source, flash it to the stm32 and debug it
debug: flash
	@echo "\033[93mStarting the debugging session...\033[39m"
	@echo "------ Enabling debugger communication... ------" >> $(LOG)
	openocd -f /usr/local/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/local/share/openocd/scripts/board/stm32f103c8_blue_pill.cfg > 2&
	@gdb-multiarch -x gdb_auto
	@pkill openocd
	@echo "\033[93mDebugging session ended.\033[39m"


# Run * make clean * if you want to remove all the additionally generated files and keep the source files only
clean:
	rm -rf build


disasm:
	@$(OBJDUMP) -D $(BUILD_FOLDER)/out/kernel.elf > $(BUILD_FOLDER)/out/disassembly.txt
