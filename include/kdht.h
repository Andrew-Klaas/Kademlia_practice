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

#define NUM_THREADS 1

class kdht {
public;
  void  start(std::string ip, std::string port);
  int   listen(void);
  void* get_in_addr(struct sockaddr *sa);

private:
  std::queue<std::function<void()>> ops_q {};
  std::queue<std::function<void()>> rcv_q {};
  std::thread dht_listen_thread {};
  std::thread dht_worker_thread {};

};


#endif
