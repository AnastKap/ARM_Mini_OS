# ARM_Mini_OS
An operating system for ARM Cortex-M3 architecture
An operating system for ARM Cortex-M3 architecture.

## Prerequisites
In order to build and debug this project, someone must have the following tools

- **ARM GNU Toolchain** (Compiler and Linker at least): GNU tools specific for ARM processors. To install write:
```
sudo apt-get install gcc-arm-none-eabi
```
- **OpenOCD** : Used to debug the microcontroller and create a server for gdb-multiarch to connect. Its installation is a little bit complex, but one way that seems to work is the following:
```
git clone https://github.com/openocd-org/openocd
cd openocd
./bootstrap
sudo apt-get install libusb-1.0-0-dev   # (without it it gives error for libusb-1.x)
./configure –enable-stlink # (without –enable st-link it won’t enable st-link debugging)
make && sudo make install
```

- **GDB-Multiarch**: Used to debug the microcontroller. To install write:
```
sudo apt-get install gdb-multiarch
```

- **STLink-Tools**: These are tools offered to program the flash memory  of *STM32* products and not only. To install write:
```
sudo apt-get install stlink-tools
```


## Building the source
To build the source, there is a *Makefile*. One can run
```
make
```
to just make the *all* target. Otherwise, someone can write
```
make <target>
```
where *target* can be one of the following

- **flash**: used to build the source and flash the microcontroller
- **debug**: used to build the source, flash the microcontroller and begin the debug session
- **clean**: cleans the folder from intermediate files created by the process of building and the log files
- **clean_obj**: cleans the folder from all the object files
- **disasm**: creates a disassembled version of the binary file


## Using the Debugger
To debug the microcontroller type
```
make debug
```
This automates the process of opening the server to communicate with the STM32 and debug it.

**Notice**: If the debugger doesn't open-up, try first by ensuring that openocd is not executing by typing
```
pkill openocd
```


## Context switching in ARM
The basic concept that an RTOS offers is the ability to run multiple processes simultaneously (in a pseudo-parallel way). This is done through context switching.

The way that context switching is implemented in ARM processors is with the help of the internal timer that most ARM-based microcontrollers (if not all) offer. This timer, which has the name SysTick, counts-down from a predetermined value and when it reaches zero, two things happen:

- An interrupt is produced (if it is enabled), which call the corresponding Interrupt Service Routine

- The SysTick value takes the predetermined value and starts down-counting again

The aforementioned interrupt of SysTick is what is going to allow the implementation of an asynchronous scheduler.


## Organization of the source code
The main file that is responsible for starting the kernel is the **boot.s**. This file calls the *kernel()* function of **kernel.c**. The directories serve the following purposes:

- **./peripherals**: has implementations of useful functions to interact with the *STM32f103c8* peripherals, like GPIOs, Timers, ADCs etc.

- **./interrupts**: contains functions used for the interrupt system

- **./context_switching**: contains functions which are related to the scheduler and the overall process of scheduling

- **./memory_management**: contains functions which manage the memory, like Process Pages and dynamic data allocation

- **./process**: contains functions and definitions for the processes, like PCB and a function to attach a new process to the scheduler

- **./clock**: here one can find definitions and functions for clock manipulation of the microcontroller and the clock configuration of the internal peripherals

## To do list
- [X] **RCC**
    - [X] System clock source from PLL
    - [X] Peripheral clock enable
        - [X] GPIO
        - [X] Timer
        - [X] ADC
- [ ] **ADC**
    - [X] Continuous mode
    - [ ] Discontinuous mode
    - [ ] Single Conversion
    - [ ] Interrupt implementation
- [ ] **Timers**
    - [ ] PWM output to pin
    - [ ] Interrupt implementation
- [ ] Dynamic allocation
    - [X] malloc()
    - [ ] free()
- [ ] Inter-Process Communication (IPC)

## Projects to highlight the usefulness of the OS
The following projects can be combined to showcase the importance of context-switching
- Robotic arm
- Mini inverter for mini motor
- Digital filter
- Neuron network
- GUI to allow an external user to run his code in a new thread
