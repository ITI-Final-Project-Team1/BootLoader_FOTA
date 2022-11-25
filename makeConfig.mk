#Copyright : Magdy
#makeConfig

Project_name := BTL_FOTA


CC     = arm-none-eabi-
CFLAGS =  -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g
#-mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g

SOURCES := $(shell find . -name '*.c')
INCLUDES := $(shell find . -name '*.h')
OBJECTS := $(addprefix $(OBJDIR)/,$(SOURCES:%.c=%.o))


SRC_dep := src
OBJDIR := obj
INCDIR := include
LIBDIR := 
LDSCRIPT := ldscripts
BINDIR := bin


INCS   := -I $(INCDIR)
LIBS   := $(LIBDIR)
SRC    := $(wildcard $(SOURCES))
As     := $(wildcard *.s)
OBJ    := $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:%.c=%.o)))
AsOBJ  := $(As: .s = $(OBJDIR)/.o )
P_BIN_DIR    := $(BINDIR)/$(Project)
