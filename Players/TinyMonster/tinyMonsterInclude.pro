CONFIG(TINYMONSTERINCLUDE_MODULE) {
} else {
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/TinyMonster.h

win32:LIBS += \
    $$PWD/../../lib/tinymonster.dll
unix:LIBS += \
    $$PWD/../../lib/libtinymonster.so

 CONFIG += TINYMONSTERINCLUDE_MODULE
 DEFINES += TINYMONSTERINCLUDE_MODULE
}
