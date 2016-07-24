#include <iostream>
#include "kdht.h"
#include "network.h"

int main(int argc, char* argv[]) {
  kdht::node node1;
  kdht::node node2;
  
  //bootstrap
  node1.start("127.0.0.1", "4222");
  node2.start("127.0.0.1", "4223");

  node2.bootstrap("127.0.0.1","4222"); //use node1 as "bootstrap" node

  node1.put("cat", "cat");
  node2.put("dog", "dog");

  auto result1 = node1.get("cat");
  auto result2 = node2.get("dog");

  std::cout << result1 << std::endl;
  std::cout << result2 << std::endl;

  node1.join();
  node2.join();

  return 0;
}


