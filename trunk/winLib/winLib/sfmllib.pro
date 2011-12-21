CONFIG(SFMLLIB_MODULE) {
} else {
INCLUDEPATH += $$PWD

win32{
HEADERS += \
    SFML/Audio.hpp \
    SFML/Config.hpp \
    SFML/Graphics.hpp \
    SFML/Network.hpp \
    SFML/System.hpp \
    SFML/Window.hpp \
    SFML/Window/Context.hpp \
    SFML/Window/Event.hpp \
    SFML/Window/Input.hpp \
    SFML/Window/OpenGL.hpp \
    SFML/Window/VideoMode.hpp \
    SFML/Window/Window.hpp \
    SFML/Window/WindowHandle.hpp \
    SFML/Window/WindowListener.hpp \
    SFML/Window/WindowSettings.hpp \
    SFML/Window/WindowStyle.hpp \
    SFML/System/Clock.hpp \
    SFML/System/Lock.hpp \
    SFML/System/Mutex.hpp \
    SFML/System/NonCopyable.hpp \
    SFML/System/Randomizer.hpp \
    SFML/System/Resource.hpp \
    SFML/System/Sleep.hpp \
    SFML/System/Thread.hpp \
    SFML/System/Unicode.hpp \
    SFML/System/Vector2.hpp \
    SFML/System/Vector3.hpp \
    SFML/System/Win32/Mutex.hpp \
    SFML/System/Win32/Thread.hpp \
    SFML/Network/Ftp.hpp \
    SFML/Network/Http.hpp \
    SFML/Network/IPAddress.hpp \
    SFML/Network/Packet.hpp \
    SFML/Network/Selector.hpp \
    SFML/Network/SelectorBase.hpp \
    SFML/Network/SocketHelper.hpp \
    SFML/Network/Sockets.hpp \
    SFML/Network/SocketTCP.hpp \
    SFML/Network/SocketUDP.hpp \
    SFML/Network/Win32/SocketHelper.hpp \
    SFML/Graphics/Color.hpp \
    SFML/Graphics/Drawable.hpp \
    SFML/Graphics/Font.hpp \
    SFML/Graphics/Glyph.hpp \
    SFML/Graphics/Image.hpp \
    SFML/Graphics/Matrix3.hpp \
    SFML/Graphics/PostFX.hpp \
    SFML/Graphics/Rect.hpp \
    SFML/Graphics/RenderTarget.hpp \
    SFML/Graphics/RenderWindow.hpp \
    SFML/Graphics/Shape.hpp \
    SFML/Graphics/Sprite.hpp \
    SFML/Graphics/String.hpp \
    SFML/Graphics/View.hpp \
    SFML/Audio/AudioResource.hpp \
    SFML/Audio/Listener.hpp \
    SFML/Audio/Music.hpp \
    SFML/Audio/Sound.hpp \
    SFML/Audio/SoundBuffer.hpp \
    SFML/Audio/SoundBufferRecorder.hpp \
    SFML/Audio/SoundRecorder.hpp \
    SFML/Audio/SoundStream.hpp

SOURCES +=
}

 CONFIG += NETWORK_MODULE
 DEFINES += NETWORK_MODULE
}

win32:LIBS += \
    $$PWD/../../lib/win32/libsfml-audio.a \
    $$PWD/../../lib/win32/libsfml-graphics.a \
    $$PWD/../../lib/win32/libsfml-network.a \
    $$PWD/../../lib/win32/libsfml-system.a \
    $$PWD/../../lib/win32/libsfml-window.a \
    $$PWD/../../lib/win32/libsfml-main.a







