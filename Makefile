CC=arm-linux-gnueabihf-gcc-4.4
CXX=arm-linux-gnueabihf-g++-4.4
LD=arm-linux-gnueabihf-ld
QT=../xbuild/qt-everywhere-opensource-src-4.6.2
INC=-I $(QT)/include/QtGui/ -I $(QT)/include/QtCore/ -I $(QT)/include/

CXXFLAGS=-O2 -marm -march=armv5te $(INC)
LDFLAGS=-s -shared

PROG=hook.so
OBJS=HackHook.o

all: $(PROG)

clean:
	-rm $(PROG) $(OBJS)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
