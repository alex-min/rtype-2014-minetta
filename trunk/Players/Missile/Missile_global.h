#ifndef MISSILE_GLOBAL_H
#define MISSILE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MISSILE_LIBRARY)
#  define MISSILESHARED_EXPORT Q_DECL_EXPORT
#else
#  define MISSILESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MISSILE_GLOBAL_H
