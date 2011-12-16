/**
 * @file BoundingBox.h
 * @brief BoundingBox
 * @author joris profili
 * @date Fri Dec 16 15:23:54 2011
 * 
 * BoundingBox
*/

#include "Object.h"

class BoundingBox
{
 public:

  BoundingBox();
  ~BoundingBox();  
  template < typename T >
    static bool	checkIntersect(Object<T> obj1, Object<T> obj2)
    {
      std::cout << std::endl;
      std::cout << "checkIntersect..." << std::endl;

      return (false);
    }
};
