#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include "MyString.h"
#include "Network.h"

class PlayerInfo
{
public:
    PlayerInfo();
    String const &              getLogin() const;
    UInt16                      getId() const;
    Network::Network *          getNetwork() const;


    void                        setLogin(String const &);
    void                        setId(UInt16 id);
    void                        setNetwork(Network::Network *);

protected:
    String                      _login;
    UInt16                      _playerId;
    Network::Network                     *_network;

};

#endif // PLAYERINFO_H
