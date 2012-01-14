#ifndef NETWORKMANAGEREXCEPTION_H
#define NETWORKMANAGEREXCEPTION_H
#include "Exception.h"

class NetworkManagerException : public Exception
{
public :
        NetworkManagerException(const std::string & s = "NetworkManager exception") :
            Exception(s) {}
};

#endif // NETWORKMANAGEREXCEPTION_H
