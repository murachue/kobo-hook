PFX=arm-linux-gnueabi
CC=$(PFX)-gcc-4.6
CXX=$(PFX)-g++-4.6
LD=$(PFX)-ld
QT=../xbuild/qt-everywhere-opensource-src-4.6.2
INC=-I $(QT)/include/QtGui/ -I $(QT)/include/QtCore/ -I $(QT)/include/

CXXFLAGS=-O2 -marm -march=armv5te $(INC)
#CXXFLAGS=-g -O2 -marm -march=armv5te $(INC)
LDFLAGS=-s -shared
#LDFLAGS=-g -shared

PROG=hook.so
OBJS=HackHook.o

all: $(PROG)

clean:
	-rm $(PROG) $(OBJS)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
