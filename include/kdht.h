#ifndef KDHT_H_
#define KDHT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <msgpack.hpp>
#include <iostream>
#include <queue>
#include <functional>
#include <thread>
#include <mutex>

#define NUM_THREADS 1

class kdht {
public:
  void  start(std::string ip, std::string port);
  int   listen(std::string port);
  void* get_in_addr(struct sockaddr *sa);
	void  bootstrap(std::string bootstrap_ip, std::string bootstrap_port);
  void  run();
	int  sendPing(std::string ip, std::string port);

  std::queue<std::function<void()>> ops_q {};
  std::queue<std::function<void()>> rcv_q {};
  std::thread dht_listen_thread {};
  std::thread dht_worker_thread {};
	std::mutex storage_mtx {};
	void helloWorld(std::string s);

  void kdht::handle_function(vector<std::string> argvec);


};


#endif
