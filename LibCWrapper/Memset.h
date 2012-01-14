#ifndef MEMSET_H_
#define MEMSET_H_
#undef ZeroMemory

namespace libc {
   void          *Memset(void *data, const char c, const unsigned int size);
   void          *ZeroMemory(void *data, const unsigned int size);
}

#endif
