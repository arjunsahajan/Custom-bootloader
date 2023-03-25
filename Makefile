CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -g -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -o0
LDFLAGS= -mcpu=$(MACH) -specs=nano.specs -mthumb -mfloat-abi=soft -T tm4c123_linker.ld -Wl,-Map=bootloader.map

all:main.o loader_apis.o clock.o wait.o tm4c123_startup.o uart0.o sha256.o uart1.o syscalls.o bootloader.elf


main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

loader_apis.o: loader_apis.c
	$(CC) $(CFLAGS) -o $@ $^

clock.o:clock.c
	$(CC) $(CFLAGS) -o $@ $^
	
wait.o:wait.c
	$(CC) $(CFLAGS) -o $@ $^

sha256.o:sha256.c
	$(CC) $(CFLAGS) -o $@ $^

tm4c123_startup.o:tm4c123_startup.c
	$(CC) $(CFLAGS) -o $@ $^

syscalls.o:syscalls.c
	$(CC) $(CFLAGS) -o $@ $^

uart0.o:uart0.c
	$(CC) $(CFLAGS) -o $@ $^

uart1.o:uart1.c
	$(CC) $(CFLAGS) -o $@ $^

bootloader.elf:main.o loader_apis.o clock.o wait.o uart0.o sha256.o uart1.o syscalls.o tm4c123_startup.o
	$(CC) $(LDFLAGS) -o $@ $^	

load:
	openocd -f ek-tm4c123gxl.cfg

clean:
	rm -rf *.o *.elf
