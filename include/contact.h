#ifndef CONTACT_H_
#define CONTACT_H_

#include <iostream>
#include <stdint.h>
#include "infohash.h"


class Contact {
  // bigendian NODEID
  // IP address
  // UDP port address 
public:
  Infohash    NodeID;
  std::string IPaddress;
  uint8_t      port;

};

#endif
