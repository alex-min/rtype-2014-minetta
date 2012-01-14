#ifndef NETWORKDISCONNECT_H
#define NETWORKDISCONNECT_H
#include "Exception.h"

class NetworkDisconnect : public Exception
{
public :
        NetworkDisconnect(const std::string & s = "NetworkDisconnect exception") :
            Exception(s) {}
};

#endif // NETWORKDISCONNECT_H
