/**
 * @file Object.h
 * @brief Object
 * @author joris profili
 * @date Fri Dec 16 15:15:26 2011
 * 
 * Object
*/

#include <iostream>

template < typename T > class Object
{
 public:
  
  Object()
    {
      _x = 0;
      _y = 0;
      _w = 0;
      _h = 0;      
    }

  Object(T x, T y, T w, T h)
    {
      _x = x;
      _y = y;
      _w = w;
      _h = h;
    }
  
  void	setX(T x)
  {
    _x = x;
  }
  void	setY(T y)
  {
    _y = y;
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
    return (_x);
  }
  
  T	getY() const
  {
    return (_y);
  }
  
  T	getH() const
  {
    return (_h);
  }
  
  T	getW() const
  {
    return (_w);
  }
  
  ~Object()
    {

    }
  
 private:

  T	_x;
  T	_y;
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