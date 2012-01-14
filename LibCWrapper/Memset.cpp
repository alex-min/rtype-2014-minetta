#include "Memset.h"

namespace libc {
  void          *Memset(void *data, const char c, const unsigned int size)
  {
    for (unsigned int i = 0; i < size; ++i) {
      static_cast<char *> (data)[i] = c;
    }
    return (data);
  }

  void          *ZeroMemory(void *data, const unsigned int size)
  {
    return (libc::Memset(data, 0, size));
  }
}
