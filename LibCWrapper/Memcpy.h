#ifndef MEMCPY_H
#define MEMCPY_H

namespace libc {
   void          *Memcpy(void *dest, const void *src, const unsigned int size);
   void          *Memadd(void *dest, const void *src, const unsigned int size,
                         unsigned int &maxSize);
   template<class T>
   T             Memextract(const void *src, const unsigned int size, unsigned int &sizeCount)
   {
       T * ref = (T *) (static_cast<const char *> (src) + sizeCount);
       sizeCount += size;
       return (*ref);
   }
}

#endif // MEMCPY_H
