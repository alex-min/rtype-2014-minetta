CONFIG(MISSILEINCLUDE_MODULE) {
} else {
INCLUDEPATH += $$PWD

HEADERS += \
    Missile.h \
    Missile_global.h

win32:LIBS += \
    $$PWD/../../lib/missile.dll
unix:LIBS += \
    $$PWD/../../lib/libmissile.so

 CONFIG += MISSILEINCLUDE_MODULE
 DEFINES += MISSILEINCLUDE_MODULE
}
