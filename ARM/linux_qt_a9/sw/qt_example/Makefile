# Build flags
SW_ROOT := $(CURDIR)/..

CXX        = $(CROSS_COMPILE)g++
MOC        = $(SW_ROOT)/packages/qt-everywhere-opensource-src-5.4.0/qtbase/bin/moc

LFLAGS     = -g -Wl,-rpath-link,$(SW_ROOT)/sdcard/sysroot/usr/lib --sysroot=$(SW_ROOT)/sdcard/sysroot -Wl,-O1 -Wl,-rpath,/usr/local/qt5/lib
LIBS       = $(SUBLIBS) -L$(SW_ROOT)/sdcard/sysroot/lib -L$(SW_ROOT)/sdcard/sysroot/usr/lib -L$(SW_ROOT)/sdcard/sysroot/usr/local/qt5/lib -lQt5Gui -lQt5Core 

INCPATH    = -I$(SW_ROOT)/sdcard/sysroot/usr/local/qt5/include
DEFINES    = -DQT_NO_MTDEV -DQT_NO_LIBUDEV -DQT_NO_EXCEPTIONS -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB
CXXFLAGS   = -g -pipe -march=armv7-a -mfpu=neon -DLINUX=1 -mfloat-abi=softfp -fno-exceptions -Wall -W -D_REENTRANT -fPIE $(DEFINES)

OBJECTS = main.o rasterwindow.o moc_rasterwindow.o

all: watch

watch: $(OBJECTS)
	$(TARGET)-g++ $(LFLAGS) main.o rasterwindow.o moc_rasterwindow.o $(LIBS) -o $@

clean:
	$(RM) -f *.o *.a *~ watch
 
.cpp.o: %.cpp Makefile
	$(CXX) -c $(CXXFLAGS) $(INCPATH) $< -o $@

moc_%.cpp: %.h
	$(MOC) $(DEFINES) $(INCPATH) $< -o $@

