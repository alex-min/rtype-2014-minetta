#include "StartGameSlot.h"

StartGameSlot::StartGameSlot()
{

}

void StartGameSlot::onCall(bool isOnTimeout, Packet *packet, Protocol::Protocol *proto, void *data)
{

    (void)isOnTimeout;
    (void)packet;
    (void)proto;
    (void)data;

    emit startGame();
}
