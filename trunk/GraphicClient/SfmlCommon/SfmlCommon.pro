CONFIG(SFMLCOMMON_MODULE) {
} else {
INCLUDEPATH += $$PWD

unix:LIBS += -lsfml-graphics -lsfml-window -lsfml-system -L/usr/X11R6/lib -lX11 -lpthread

HEADERS += \
    $$PWD/Image.h \
    $$PWD/AnimatedImage.h

SOURCES += \
    $$PWD/Image.cpp \
    $$PWD/AnimatedImage.cpp

 CONFIG += SFMLCOMMON_MODULE
 DEFINES += SFMLCOMMON_MODULE
}
