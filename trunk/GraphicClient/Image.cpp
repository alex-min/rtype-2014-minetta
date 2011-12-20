#include "Image.h"

Image::Image()
{
    _imageLoaded = false;
}

Image::Image(std::string const &filename)
{
    if (loadImage(filename) == false)
        std::cout << "Error loading " << filename << std::endl;
}

bool    Image::loadImage(std::string const &filename)
{
    if (_image.LoadFromFile(std::string(IMAGEPATH) + filename) == false)
        return (false);

    _sprite.SetImage(_image);
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

Image::~Image()
{

}
