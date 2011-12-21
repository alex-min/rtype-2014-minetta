#include "AnimatedImage.h"

AnimatedImage::AnimatedImage() : Image()
{
}

AnimatedImage::AnimatedImage(std::string const &filename) : Image(filename)
{

}

bool    AnimatedImage::parseFile()
{
    if (_imageLoaded == false)
        return (false);

    int sizeX = _sprite.GetSize().x;
    int sizeY = _sprite.GetSize().y;
    int beginY = 0;
    int endY = 0;
    int beginX = 0;
    int endX = 0;
    bool pixelOnLine = false;
    bool pixelOnColumn = false;

    for (int y = 0; y < sizeY; y++)
    {
        bool pixLineTest = false;

        for (int x = 0; x < sizeX; x++)
        {
            if (_sprite.GetPixel(x, y).a != 0 && pixelOnLine == false)
            {
                beginY = y;
                pixelOnLine = true;
            }
            if (_sprite.GetPixel(x, y).a != 0)
                pixLineTest = true;
        }

        if (pixLineTest == false && pixelOnLine == true)
        {
            endY = y;

            for (int tmpX = 0; tmpX < sizeX; ++tmpX)
            {
                bool pixColumnTest = false;

                for (int tmpY = beginY; tmpY < endY; ++tmpY)
                {
                    if (_sprite.GetPixel(tmpX, tmpY).a != 0 && pixelOnColumn == false)
                    {
                        beginX = tmpX;
                        pixelOnColumn = true;
                    }

                    if (_sprite.GetPixel(tmpX, tmpY).a != 0)
                        pixColumnTest = true;
                }

                if (pixColumnTest == false && pixelOnColumn == true)
                {
                    endX = tmpX;

                    sf::Sprite *sprite = new sf::Sprite(_image);

                    sprite->SetSubRect(sf::Rect<int>(beginX, beginY, endX, endY));

                    sprite->SetPosition(0, 0);

                    _monsters.push_back(sprite);

                    pixelOnLine = false;
                    pixelOnColumn = false;
                }
            }
        }
    }

    return (true);
}

std::list<sf::Sprite*>   const &AnimatedImage::getMonsters()
{
    return (_monsters);
}

AnimatedImage::~AnimatedImage()
{

}
