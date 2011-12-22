#ifndef TINYMONSTER_H
#define TINYMONSTER_H

#include <math.h>
#include "APlayer.h"
#include "Exception.h"

#include <QtCore/qglobal.h>

#if defined(TINYMONSTER_LIBRARY)
#  define TINYMONSTERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TINYMONSTERSHARED_EXPORT Q_DECL_IMPORT
#endif

class TINYMONSTERSHARED_EXPORT TinyMonster : public APlayer
{
public:
    TinyMonster(unsigned int screenWidth, unsigned int screenHeight, unsigned int amplitude,
               unsigned int origine, unsigned int nbOscillation = 10);
    virtual void            shoot();
    virtual void            move(const Direction &);
    virtual void            doSomeActions(int time);
    virtual ~TinyMonster();
private:
    unsigned int _screenWidth;
    unsigned int _screenHeight;
    unsigned int _totalTime;
    unsigned int _amplitude;
    unsigned int _origine;
    unsigned int _nbOscillation;
};

#endif // TINYMONSTER_H
