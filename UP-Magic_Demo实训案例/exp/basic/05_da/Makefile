
#TOPDIR  := $(shell cd ..; pwd)
TOPDIR  := .


#KERNELDIR = /usr/src/linux
#KERNELDIR = /opt/host/armv4l/src/linux
KERNELDIR = /arm2410cl/kernel/linux-2.4.18-2410cl/
INCLUDEDIR = $(KERNELDIR)/include

CROSS_COMPILE=armv4l-unknown-linux-

AS      =$(CROSS_COMPILE)as
LD      =$(CROSS_COMPILE)ld
CC      =$(CROSS_COMPILE)gcc
CPP     =$(CC) -E
AR      =$(CROSS_COMPILE)ar
NM      =$(CROSS_COMPILE)nm
STRIP   =$(CROSS_COMPILE)strip
OBJCOPY =$(CROSS_COMPILE)objcopy
OBJDUMP =$(CROSS_COMPILE)objdump



CFLAGS += -I..
CFLAGS += -Wall -O -D__KERNEL__ -DMODULE -I$(INCLUDEDIR)


TARGET = s3c2410-exio.o  da_main

all: $(TARGET)


s3c2410-exio.o:s3c2410-exio.c
	$(CC) -c $(CFLAGS) $^ -o $@
da_main:da_main.o
	$(CC) $^ -o $@

clean:
	rm -f *.o *~ core .depend
