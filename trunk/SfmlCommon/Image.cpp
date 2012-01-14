#include "Image.h"

Image::Image()
{
    _imageLoaded = false;
    _name = "";
    _fullName = "";
}

Image::Image(std::string const &filename)
{
    if (loadImage(filename) == false)
        std::cout << "Error loading " << filename << std::endl;
}

sf::Image  const &Image::getImage() const
{
    return (_image);
}

bool    Image::loadImage(std::string const &filename)
{
    if (_image.LoadFromFile(std::string(IMAGEPATH) + filename) == false)
        return (false);

    _sprite.SetImage(_image);
    _name = filename;
    _fullName = (std::string(IMAGEPATH) + filename);
    _imageLoaded = true;
    return (true);
}

bool    Image::hasImageLoaded() const
{
    return (_imageLoaded);
}

void    Image::setSprite(sf::Image const &image)
{
    _sprite.SetImage(image);
}

sf::Sprite  &Image::getSprite()
{
    return (_sprite);
}

std::string const &Image::getName() const
{
    return (_name);
}

std::string const &Image::getFullName() const
{
    return (_fullName);
}

Image::~Image()
{

}
