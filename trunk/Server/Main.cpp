#include <iostream>
#include "IpAddress.h"

#ifndef COMMON_MODULE
#error "Common module not found"
#endif

int	main(int ac, char **av)
{
    Network::IpAddress i(127,0,0,1);

    std::cout << i.toString() << std::endl;
  std::cout << "Hello world" << std::endl;
  return (0);
}
