#ifndef SYSTEMDEFINES_H
#define SYSTEMDEFINES_H

typedef unsigned long long UInt64;
typedef long long Int64;
typedef long Int32;
typedef short Int16;
typedef char Int8;
typedef unsigned long UInt32;
typedef unsigned short UInt16;
typedef unsigned char UInt8;
typedef unsigned char Byte;

#define PACKED __attribute__((packed))

#define LOG std::cout << __FILE__ << ":" << __LINE__ << " " << __func__ << ": "
#define LOGERR std::cerr << __FILE__ << ":" << __LINE__ << " " << __func__ << ": "

#endif // SYSTEMDEFINES_H
