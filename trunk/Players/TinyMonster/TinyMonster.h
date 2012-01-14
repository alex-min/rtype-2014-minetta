#ifndef TINYMONSTER_H
#define TINYMONSTER_H

#include <math.h>
#include "APlayer.h"
#include "Exception.h"
#include "Missile.h"

#include <QtCore/qglobal.h>

#if defined(TINYMONSTER_LIBRARY)
#  define TINYMONSTERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TINYMONSTERSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace Player
{
    typedef IPlayer* (*missileFactory)();
}

class TINYMONSTERSHARED_EXPORT TinyMonster : public APlayer
{
public:
    TinyMonster();
    virtual IPlayer         *shoot(void *fct);
    virtual void            update(UInt32 time);
    virtual                 ~TinyMonster();
    int                     getAmplitude();
    void                    setAmplitude(UInt32 amplitude);
    int                     getNbOscillation();
    void                    setNbOscillation(UInt32 nbOscillation);
    virtual void            erase();
    virtual bool            isOutOfScreen();
    virtual void            setPosition(float x, float y);
private:
    UInt32  _totalTime;
    UInt32  _shootTime;
    UInt32  _lastShootTime;
    UInt32  _amplitude;
    UInt32  _nbOscillation;
    bool    _wantToShoot;
};

#endif // TINYMONSTER_H
