#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "Point.h"

template < typename T > class Object
{
public:

    Object()
    {
        _pos.setCoord(0, 0);
        _w = 0;
        _h = 0;
    }

    Object(T x, T y, T w, T h)
    {
        _pos.setCoord(x, y);
        _w = w;
        _h = h;
    }

    virtual void  setPositionWithoutOld(T x, T y) {
        _pos.setCoord(x, y);
    }

    virtual void  setPosition(T x, T y)
    {
        _oldPos = _pos;

        _pos.setCoord(x, y);
    }

    virtual void  setOldPosition(T x, T y)
    {
        _oldPos.setCoord(x, y);
    }

    Point<T> const &getOldPos()
    {
        return (_oldPos);
    }

    void	setX(T x)
    {
        _pos.setX(x);
    }
    void	setY(T y)
    {
        _pos.setY(y);
    }

    void	setH(T h)
    {
        _h = h;
    }

    void	setW(T w)
    {
        _w = w;
    }

    T	getX() const
    {
        return (_pos.getX());
    }

    T	getY() const
    {
        return (_pos.getY());
    }

    Point<T> const &getPosition()
    {
        return (_pos);
    }

    T	getH() const
    {
        return (_h);
    }

    T	getW() const
    {
        return (_w);
    }

    bool	intersectWith(Object<T> obj)
    {
        if (obj.getX() > (_pos.getX() + _w))
            return (false);

        if ((obj.getX() + obj.getW()) < _pos.getX())
            return (false);

        if (obj.getY() > (_pos.getY() + _h))
            return (false);

        if ((obj.getY() + obj.getH()) < _pos.getY())
            return (false);

        return (true);
    }

    ~Object()
    {

    }

protected:

    Point<T> _pos;
    Point<T> _oldPos;
    T	_h;
    T	_w;
};

template < typename T >
std::ostream &operator<<(std::ostream &stream, Object< T > &obj)
{
    stream << "Object:" << std::endl;
    stream << "-> x: " << obj.getX() << std::endl;
    stream << "-> y: " << obj.getY() << std::endl;
    stream << "-> width: " << obj.getW() << std::endl;
    stream << "-> height: " << obj.getH();

    return (stream);
}

typedef Object<int>	ObjectI;
typedef Object<float>	ObjectF;
typedef Object<double>	ObjectD;

#endif /*OBJECT_H*/
