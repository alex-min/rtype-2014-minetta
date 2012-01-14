#ifndef SCROLLING_H_
#define SCROLLING_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "MyString.h"

class MyCanvas;
class	Scrolling
{
public:
  Scrolling();
  ~Scrolling();
  void		loadBackground(std::string const & First, std::string const & Second);
  void		scroll();
  void		affBackground(MyCanvas *app);
  
private:
  sf::Image		Back1;
  sf::Image		Back2;
  sf::Sprite	First;
  sf::Sprite	Second;
  sf::Sprite	Tmp;
  sf::Vector2f	FPos;
  sf::Vector2f	SPos;
  sf::Vector2f	FSize;
  sf::Vector2f	SSize;
};
#endif
