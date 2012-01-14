#include "Memcpy.h"

namespace libc {
    void          *Memcpy(void *dest, const void *src, const unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++) {
            reinterpret_cast<char *> (dest)[i] = reinterpret_cast<const char *>(src)[i];
        }
        return (dest);
    }

    void          *Memadd(void *dest, const void *src, const unsigned int size,
                          unsigned int &maxSize)
    {
        for (unsigned int i = maxSize; i < size + maxSize; i++) {
            reinterpret_cast<char *> (dest)[i] = reinterpret_cast<const char *>(src)[i - maxSize];
        }
        maxSize += size;
        return (dest);
    }


}
