#include "EventReceiver.h"
#include <iostream>

EventReceiver::EventReceiver()
{

}

bool EventReceiver::OnEvent(sf::Event &event)
{
    if (event.Type == sf::Event::KeyPressed)
        _key_pressed[event.Key.Code] = true;
    else if (event.Type == sf::Event::KeyReleased)
        _key_pressed[event.Key.Code] = false;

    return (false);
}

bool EventReceiver::isKeyPressed(sf::Key::Code key) const
{
    std::map<sf::Key::Code, bool>::const_iterator it = _key_pressed.find(key);

    if (it == _key_pressed.end())
        return (false);
    return (it->second);
    return (false);
}

