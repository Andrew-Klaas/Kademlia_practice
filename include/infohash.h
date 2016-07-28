#ifndef INFOHASH_H_
#define INFOHASH_H_

#include <array>
#include <cstdint>
#include <cstring>

#define ID_BYTE_LENGTH 20

class Infohash {
public:
  std::array<char, ID_BYTE_LENGTH> ID;
  
  bool operator<(const Infohash &other) const {
    for (auto i = 0; i < ID_BYTE_LENGTH; i++ ) {
      if(this->ID[i] > other.ID[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator==(const Infohash &other) const {
    return std::memcmp(this->ID.data(), other.ID.data(), ID_BYTE_LENGTH) == 0;
  }

private:
  


};

#endif
