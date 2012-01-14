#ifndef SFML_H
#define SFML_H

#ifdef OS_WINDOWS
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#else
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

#endif
#endif // SFML_H
