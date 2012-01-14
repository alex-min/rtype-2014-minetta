CONFIG(SFMLCOMMON_MODULE) {
} else {
INCLUDEPATH += $$PWD
include(../Common/Common.pro)
include(../lib/win32/WinSFML.pro)

unix:LIBS += -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -L/usr/X11R6/lib -lX11 -lpthread

HEADERS += \
    $$PWD/Image.h \
    $$PWD/AnimatedImage.h \
    $$PWD/EventReceiver.h \
    $$PWD/Sfml.h

SOURCES += \
    $$PWD/Image.cpp \
    $$PWD/AnimatedImage.cpp \
    $$PWD/EventReceiver.cpp

 CONFIG += SFMLCOMMON_MODULE
 DEFINES += SFMLCOMMON_MODULE
}
