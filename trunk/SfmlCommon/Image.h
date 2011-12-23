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
    virtual bool    hasImageLoaded() const;
    virtual bool    loadImage(std::string const &filename);
    virtual std::string const &getName() const;
    virtual std::string const &getFullName() const;
    virtual void    setSprite(sf::Image const &image);
    virtual sf::Sprite &getSprite();
    virtual sf::Image  const &getImage() const;
    virtual ~Image();

protected:

    bool        _imageLoaded;
    sf::Image   _image;
    sf::Sprite  _sprite;
    std::string _name;
    std::string _fullName;
};

#endif // IMAGE_H
