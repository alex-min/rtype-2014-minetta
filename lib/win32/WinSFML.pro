CONFIG(WINSFML_MODULE) {
} else {
win32:INCLUDEPATH += $$PWD/include

win32:LIBS += $$PWD/lib/libsfml-system.a \
    $$PWD/lib/libsfml-window.a \
    $$PWD/lib/libsfml-graphics.a \
    $$PWD/lib/libsfml-audio.a \
    $$PWD/lib/libsfml-network.a
 CONFIG += WINSFML_MODULE
 DEFINES += WINSFML_MODULE
}
