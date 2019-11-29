TOPDIR = ../
include $(TOPDIR)/Rules.mak

EXTRA_LIBS += -lpthread

EXEC= ./canchat $(INSTALL_DIR)/canchat

OBJS= main.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)  $(EXTRA_LIBS)  

install:
	$(EXP_INSTALL) $(EXEC) $(INSTALL_DIR)

clean:
	rm -f *.o a.out canchat *.gdb
