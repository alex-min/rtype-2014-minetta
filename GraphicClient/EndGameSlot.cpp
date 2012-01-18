#include "EndGameSlot.h"

EndGameSlot::EndGameSlot()
{

}

void EndGameSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data)
{
    if (isOnTimeout || !packet || !proto || !data)
        return ;

    std::cout << "END GAME SLOT" << std::endl;

    emit endGame();
}
