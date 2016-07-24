#include <iostream>
#include "gtest/test"
#include "kademalia_practice.h"

int main(int argc, char* argvp[]) {
  kdht::Node node1;
  kdht::Node node2;

  node1.run(5000);
  node2.run(5001);

  node2.bootstrap("localhost","5000");

  int8_t value1 = 5;
  int8_t value2 = 6;

  node1.put("cat", );
  node2.put("dog", );

  auto result = node1.get("cat");
  std::cout << "result is: " << result << std::endl;

  auto result2 = node2.get("dog");
  std::cout << "result is: " << result2 << std::endl;

  node1.join();
  node2.join();

}
