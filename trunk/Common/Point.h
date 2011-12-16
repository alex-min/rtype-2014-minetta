/**
 * @file Point.h
 * @brief Point
 * @author joris profili
 * @date Fri Dec 16 15:27:32 2011
 * 
 * Point
*/

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

typedef Point<int>	PointI;
typedef Point<float>	PointF;
typedef Point<double>	PointD;
