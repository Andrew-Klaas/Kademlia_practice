#include <iostream>
#include <queue>
#include <functional>
#include <utility>
#include <thread>
#include <chrono>         // std::chrono::seconds

std::mutex storage_mtx {};
std::queue<std::function<void()>> ops_queue;  
bool running;

void task1(std::string msg) {
    std::cout << "task1 says: " << msg << std::endl;
    running = true;
    while (running) {
     std::lock_guard<std::mutex> lck(storage_mtx);
     auto ops = std::move(ops_queue);
     if (!ops.empty()) {
        ops.front()();
     }
   }
}

void helloWorld(std::string str) {
  std::cout << str << std::endl;
}

int main(int argc, char* argv[]) {


  std::thread t1(task1, "Hello");

  std::string my_string = "hello!";

  std::cout << "before first emplace" << std::endl;

  { 
    std::lock_guard<std::mutex> lck(storage_mtx);
    ops_queue.emplace([=]() {
      helloWorld(my_string);
    });
  }
 
  //std::cout << "here1" << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(1));
  {
    std::lock_guard<std::mutex> lck(storage_mtx);
    ops_queue.emplace([=]() {
      helloWorld("motna");
    });
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));
  
  //std::cout << "here2" << std::endl;
  {
    std::lock_guard<std::mutex> lck(storage_mtx);
    ops_queue.emplace([=]() {
      helloWorld("fucka");
    });
  }

  running = false;
  t1.join();

  // How to execute callback off of queue;
  //ops_queue.front()();

  //auto fn = ops_queue.front();
  //fn();

}

/*
   std::queue<std::function<void(SecureDht&)>> pending_ops_prio {};
    std::queue<std::function<void(SecureDht&)>> pending_ops {};
    std::mutex storage_mtx {};

   pending_ops.emplace([=](SecureDht& dht) mutable {
        dht.get(hash, vcb, dcb, std::move(f), std::move(w));
    });


    std::lock_guard<std::mutex> lck(storage_mtx);
        ops = std::move(pending_ops_prio);
*/



