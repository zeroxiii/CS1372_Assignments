PRODUCT_NAME = test
DKPATH = /opt/devkitARM/bin
SOURCES = main.c

ELF_NAME = $(PRODUCT_NAME).elf
ROM_NAME = $(PRODUCT_NAME).gba

MODEL = -mthumb-interwork -mthumb
SPECS = -specs=gba_mb.specs

AS = $(DKPATH)/arm-eabi-as
ASFLAGS = -mthumb-interwork

CC = $(DKPATH)/arm-eabi-gcc
CFLAGS = $(MODEL) -O2 -Wall

LD = $(DKPATH)/arm-eabi-gcc
LDFLAGS = $(SPECS) $(MODEL)

OBJCOPY = $(DKPATH)/arm-eabi-objcopy
OBJCOPYFLAGS = -O binary

GBAFIX = $(DKPATH)/gbafix

OBJECTS = $(SOURCES:.c=.o)

# --- Main build target
all: build

run :
	open $(ROM_NAME)

build : $(ROM_NAME)

# --- Build .elf file into .gba ROM file
$(ROM_NAME) : $(ELF_NAME)
	$(OBJCOPY) $(OBJCOPYFLAGS) $(ELF_NAME) $(ROM_NAME)
	$(GBAFIX) $(ROM_NAME)
	
# --- Build .o files into .elf file
$(ELF_NAME) : $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@

# -- Build .c files into .o files
$(OBJECTS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rfv $(ROM_NAME)
	@rm -rfv $(ELF_NAME)
	@rm -rfv *.o