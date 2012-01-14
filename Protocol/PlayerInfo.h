#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include "MyString.h"
#include "Network.h"
#include "IPlayer.h"

class PlayerInfo
{
public:
    PlayerInfo();
    PlayerInfo(String const &login);
    PlayerInfo(Network::Network *net);
    PlayerInfo(UInt16 id);

    // should not be const
    IPlayer                     *getPlayer();
    String const &              getLogin() const;
    UInt16                      getId() const;
    Network::Network const *    getNetwork() const;
    Network::Network *          getNetwork();


    void                        setLogin(String const &);
    void                        setId(UInt16 id);
    void                        setNetwork(Network::Network const *);
    void                        setPlayer(IPlayer *);

    void                        erase();

protected:
    String                      _login;
    UInt16                      _playerId;
    Network::Network const      *_network;
    static UInt16               _playerCountId;
    IPlayer                     *_player;
};

#endif // PLAYERINFO_H
