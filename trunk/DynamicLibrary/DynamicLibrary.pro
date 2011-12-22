CONFIG(DYNAMICLIB_MODULE) {
} else {
INCLUDEPATH += $$PWD

include(../Common/common.pro)

win32: DEFINES += OS_WINDOWS
unix: DEFINES += OS_UNIX


win32:SOURCES += $$PWD/WinDynaLib.cpp
win32:HEADERS += $$PWD/WinDynaLib.hpp
unix:SOURCES  += $$PWD/UnixDynaLib.cpp
unix:HEADERS += $$PWD/UnixDynaLib.hpp


DEFINES += DYNAMICLIB_MODULE
CONFIG += DYNAMICLIB_MODULE
}

HEADERS += \
    IDynaLib.hpp \

SOURCES += \
    main.cpp


















