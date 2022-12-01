#Copyright : Magdy
#makeConfig

CC     = arm-none-eabi-
CFLAGS =  -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g
#-mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g

SOURCES := $(shell find . -name '*.c')
INCLUDES := $(shell find . -name '*.h')


SRC_dep := src
OBJDIR := Release/obj
INCDIR := include
LIBDIR := 
LDSCRIPT := ldscripts
BINDIR := Release/bin


INCS   := -I $(INCDIR)
LIBS   := $(LIBDIR)
SRC    := $(wildcard $(SOURCES))
As     := $(wildcard *.s)
OBJ    := $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:%.c=%.o)))
AsOBJ  := $(As: .s = $(OBJDIR)/.o )
P_BIN_DIR    := $(BINDIR)/$(Project)

OBJECTS := $(addprefix $(OBJDIR)/,$(SOURCES:%.c=%.o))


Project_name := BTL_FOTA


