#ifndef EVENTRECEIVER_H_
#define EVENTRECEIVER_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <irr/IEventReceiver.h>
#include <map>


class EventReceiver
{
 
public:
  EventReceiver();
 
  bool OnEvent(sf::Event &event);
  bool isKeyPressed(sf::Key::Code) const;

private:
  std::map< sf::Key::Code, bool >	_key_pressed;
};


#endif
