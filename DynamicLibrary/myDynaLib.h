#ifndef MYDYNALIB_H
#define MYDYNALIB_H

#include "IDynaLib.hpp"
#ifdef OS_WINDOWS
#include "WinDynaLib.hpp"
typedef WinDynaLib MyDynaLib;
#elif defined OS_UNIX
#include "UnixDynaLib.hpp"
typedef UnixDynaLib MyDynaLib;
#else
#error "MyDynalib.h : Framwork doesnt have a Dynamic library loader implementation for your operating system"
#endif

#endif // MYDYNALIB_H
