#ifndef LOGINMAPPER_H
#define LOGINMAPPER_H
#include <list>
#include "Network.h"
#include "MyString.h"
#include "SystemDefines.h"
#include "PlayerInfo.h"
#include "Pool.h"

namespace Protocol {
class LoginMapper
{
public:
    typedef std::list< PlayerInfo * > MapperType;

    LoginMapper();
    // cannot be const
    PlayerInfo     *getByLogin(String const &login);
    PlayerInfo     *getByNetwork(Network::Network const * network);
    PlayerInfo     *getById(UInt16 id);
    MapperType     &getMapperList();
    MapperType const    &getMapperList() const;

    PlayerInfo     *addPlayer(PlayerInfo *);
    PlayerInfo     *addPlayer(String const &);
    PlayerInfo     *addPlayer(Network::Network const *network);
    PlayerInfo     *addPlayer(UInt16 id);

    void            removePlayer(PlayerInfo *);

    bool        exist(String const &login);

protected:
    PoolFactory < PlayerInfo >                    _playerPool;
    MapperType                                    _mapping;
    UInt16                                        _playerId;
    String const &                                _invalidString;
};
} // !namespace : Protocol

#endif // LOGINMAPPER_H
