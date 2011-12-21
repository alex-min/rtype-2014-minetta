CONFIG(SFMLCOMMON_MODULE) {
} else {
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/Image.h \
    $$PWD/AnimatedImage.h

SOURCES += \
    $$PWD/Image.cpp \
    $$PWD/AnimatedImage.cpp

 CONFIG += SFMLCOMMON_MODULE
 DEFINES += SFMLCOMMON_MODULE
}
