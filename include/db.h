#ifndef DB_H_
#define DB_H_

#include "infohash.h"
#include <vector>

class db {

public:
  std::vector<std::pair<Infohash, std::string>> data;

};

#endif

