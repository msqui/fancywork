#ifndef __NULLPTR_H__
#define __NULLPTR_H__

#include <boost/shared_ptr.hpp>
/**
 * Represents boost::shared_ptr<T> equivalent to null-ptr
**/
class NullPtr
{
public:
  template <typename T>
  operator boost::shared_ptr<T>()
  {
    return boost::shared_ptr<T>();
  }
};

extern NullPtr nullPtr;

#endif /* end of include guard: __NULLPTR_H__ */
