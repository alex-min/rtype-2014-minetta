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
    TinyMonster();
    virtual void            shoot(void *);
    void    update(UInt32 time);
    virtual ~TinyMonster();
    int getAmplitude();
    void setAmplitude(UInt32 amplitude);
    int getNbOscillation();
    void setNbOscillation(UInt32 nbOscillation);
    bool isOutOfScreen();
private:
    unsigned int _totalTime;
    unsigned int _amplitude;
    unsigned int _origine;
    unsigned int _nbOscillation;
};

extern "C"
{
TINYMONSTERSHARED_EXPORT IPlayer *createAndFill(UInt32 screenWidth, UInt32 screenHeight,
                    UInt32 amplitude, UInt32 origine, UInt32 nbOscillation)
    {
        TinyMonster *monster = new TinyMonster();
        monster->setScreenSize(screenWidth, screenHeight);
        monster->setAmplitude(amplitude);
        monster->setPosition(screenWidth, origine);
        monster->setNbOscillation(nbOscillation);
        return (monster);
    }
TINYMONSTERSHARED_EXPORT IPlayer *create()
{
    return (new TinyMonster());
}
}
#endif // TINYMONSTER_H
