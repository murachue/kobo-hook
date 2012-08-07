CC=arm-linux-gnueabihf-gcc-4.4
QT=../xbuild/qt-everywhere-opensource-src-4.6.2
INC=-I $(QT)/include/QtGui/ -I $(QT)/include/QtCore/ -I $(QT)/include/

all: hook.so

hook.so: HackHook.cpp
	$(CC) $< -shared -o $@ $(INC) -marm -march=armv5te
