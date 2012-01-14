#ifndef POINT_H
#define POINT_H
#include <math.h>

#include <iostream>

template < typename T> class Point
{
public:

    Point()
    {

    }

    Point(T x, T y)
    {
        _x = x;
        _y = y;
    }

    Point(Point<T> const &point)
    {
        _x = point.getX();
        _y = point.getY();
    }

    Point<T> const operator=(Point<T> const &point)
    {
        if (this != &point)
        {
            _x = point.getX();
            _y = point.getY();
        }

        return (*this);
    }

    bool    operator ==(Point<T> const &p) {
        if (this == &p)
            return (true);
        if (this->_x == p._x && this->_y == p._y)
            return (true);
        return (false);
    }

    void    normalize() {
        Point<T> tmp = *this;
        T norm = ::sqrt(_x * _x + _y * _y);
        this->_x = tmp._x / norm;
        this->_y = tmp._y / norm;
    }

    void  setCoord(T x, T y)
    {
        _x = x;
        _y = y;
    }

    void	setX(T x)
    {
        _x = x;
    }

    void	setY(T y)
    {
        _y = y;
    }

    T	getX() const
    {
        return (_x);
    }

    T	getY() const
    {
        return (_y);
    }

    ~Point()
    {

    }

private:

    T	_x;
    T	_y;
};

template < typename T >
std::ostream &operator<<(std::ostream &stream, Point< T > &obj)
{
    stream << "Point:" << std::endl;
    stream << "-> x: " << obj.getX() << std::endl;
    stream << "-> y: " << obj.getY() << std::endl;
    return (stream);
}

typedef Point<int>	PointI;
typedef Point<float>	PointF;
typedef Point<double>	PointD;

#endif /*POINT_H*/
