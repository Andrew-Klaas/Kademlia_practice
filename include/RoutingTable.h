#ifndef ROUTINGTABLE_H_
#define ROUTINGTABLE_H_

#include "contact.h"
#include <list>
#include <memory>

#define NUM_BUCKETS 160

struct Bucket {

public:
  std::list<std::shared_ptr<Contact>> Contacts {};

};

class RoutingTable {
  
public:
  // Need to figure out size here
  // want to use NUM_BUCKETS
  std::list<std::shared_ptr<Bucket>> Buckets {};

};

#endif
