CONFIG(DYNAMICLIB_MODULE) {
} else {
INCLUDEPATH += $$PWD

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX


win32: SOURCES += $$PWD/Win32Dynalib.cpp \
                  $$PWD/Win32Dynalib.cpp \

unix:  SOURCES += $$PWD/UNIXDynalib.cpp \
                  $$PWD/UNIXDynalib.cpp \



DEFINES += DYNAMICLIB_MODULE
CONFIG += DYNAMICLIB_MODULE
}
