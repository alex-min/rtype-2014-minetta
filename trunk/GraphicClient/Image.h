#ifndef IMAGE_H
#define IMAGE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#define IMAGEPATH ("../img/")

class Image
{
public:

    Image();
    Image(std::string const &filename);
    bool    hasImageLoaded() const;
    bool    loadImage(std::string const &filename);
    void    setSprite(sf::Image const &image);
    sf::Sprite &getSprite();
    ~Image();

protected:

    bool        _imageLoaded;
    sf::Image   _image;
    sf::Sprite  _sprite;
};

#endif // IMAGE_H
