#ifndef LOGINMAPPER_H
#define LOGINMAPPER_H
#include <list>
#include "Network.h"
#include "MyString.h"
#include "SystemDefines.h"
#include "PlayerInfo.h"

namespace Protocol {
class LoginMapper
{
public:
    typedef std::list< PlayerInfo * > MapperType;

    LoginMapper();
    PlayerInfo     *getByLogin(String const &login);
    PlayerInfo     *getByNetwork(Network::Network const * network);
    PlayerInfo     *getById(UInt16 id);

    bool        exist(String const &login);

protected:
    MapperType                                    _mapping;
    UInt16                                        _playerId;
    String const &                                _invalidString;
};
} // !namespace : Protocol

#endif // LOGINMAPPER_H
