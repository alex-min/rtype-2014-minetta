#ifndef WALL_H
#define WALL_H
#include "Object.h"
#include "SystemDefines.h"

class Wall : public Object < float >
{
public:
    Wall() :
        _id(0),
        _sprite(NULL),
        _screenWidth(0),
        _screenHeight(0)  {}

    void    setSprite(void *sprite) { _sprite = sprite; }
    void    *getSprite() const { return (_sprite); }
    void    setScreenSize(UInt32 screenWidth, UInt32 screenHeight) {
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
    }
    UInt32    getScreenHeight() const { return (_screenHeight); }
    UInt32    getScreenWidth() const { return (_screenWidth); }

    void      invalidateEvent() {}
    void      erase() {}
    void      setId(UInt16 id) { _id = id; }
    UInt16    getId() const { return (_id); }

private:
    UInt16      _id;
    void        *_sprite;
    UInt32      _screenWidth;
    UInt32      _screenHeight;

};

#endif // WALL_H
