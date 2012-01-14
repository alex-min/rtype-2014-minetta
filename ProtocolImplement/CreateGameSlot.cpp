#include "CreateGameSlot.h"

void CreateGameSlot::onCall(bool, Packet *packet, Protocol::Protocol *proto, void *c)
{
    Protocol::StatusId s;
    ServerCore *core = reinterpret_cast<ServerCore *> (c);

    String mapName = proto->getLoginFromData(packet->getData(), packet->getHeader()._len);
    LOG << "MapName:" << mapName << std::endl;

    if ((packet->getHeader()._len != mapName.size() + 3) ||(mapName == "") || (mapName.size() >= 25))
    {
        s = Protocol::FAILED;
        proto->send(packet->getNetwork(), Protocol::CREATE_GAME,
                    &s, sizeof(Protocol::StatusId), packet->getHeader()._packetId);
    }
    else
    {
        UInt8 *data = static_cast<UInt8 *>(packet->getData());
        UInt8 mapId = *(data + mapName.size() + 1);
        UInt8 nbPl = *(data + mapName.size() + 2);
        LOG << "MapID:" << mapId << " -MaxNbPl:" << (int) nbPl << std::endl;
        nbPl = ((nbPl > 4) ? 4 : nbPl);
        LOG << "MapID:" << mapId << " -MaxNbPl:" << (int) nbPl << std::endl;

        ServerGame *game = core->createGame(mapName);
        game->setMapId(mapId);
        game->setMaxNbPlayer(nbPl);
        if (game) {
            s = Protocol::OK;
            proto->send(packet->getNetwork(), Protocol::CREATE_GAME, &s, sizeof(Protocol::StatusId),
                        packet->getHeader()._packetId);
        } else {
            s = Protocol::USED;
            proto->send(packet->getNetwork(), Protocol::CREATE_GAME, &s, sizeof(Protocol::StatusId),
                        packet->getHeader()._packetId);
        }
    }
}
