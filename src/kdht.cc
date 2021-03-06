#include "kdht.h"

void kdht::start(std::string ip, std::string port) {
  unsigned int nthreads = std::thread::hardware_concurrency();
	
	nodeInfoHash.setRandom();

  	
	

	// start listener thread
  //dht_listen_thread = std::thread(listen(port));
  //dht_listen_thread = std::thread([&] { this->listen(port); });
	//auto t = std::thread([&] { this->listen(port); });
  //dht_listen_thread =  std::thread(&kdht::listen, this, port);


  //dht_worker_thread = std::thread(&kdht::run, this);


}

//worker threads watching queues
void kdht::run(){
	  bool running = true;
    while (running) {
      std::lock_guard<std::mutex> lck(storage_mtx);
      auto ops = std::move(rcv_q);
      if (!ops.empty()) {
        printf("runner executing op\n");
        ops.front()();
      }
    } 
}

void kdht::bootstrap(std::string bootstrap_ip, std::string bootstrap_port) {
	auto result = sendPing(bootstrap_ip, bootstrap_port);

}

int kdht::sendPing(std::string ip, std::string port) {
	printf("sending Ping\n");
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	if ((rv = getaddrinfo(ip.c_str(), port.c_str(), &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	
	//loop through all the results of servinfo
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}

		break;
	}


	if  (p == NULL) {
		fprintf(stderr,"talker: failed to create socket\n");
		return 2;
	}

   /*
	msgpack::sbuffer buffer;
	msgpack::packer<msgpack::sbuffer> pk(&buffer);
	pk.pack_map(3);
	// function
	pk.pack(std::string("F"));
	pk.pack(0);
	// key
	pk.pack(std::string("K"));
	pk.pack(2);
	// value
	pk.pack(std::string("V"));
	pk.pack(3);
  */
  std::vector<std::string> vec;
  vec.push_back("0");
  vec.push_back("K");
  vec.push_back("cat");
  vec.push_back("V");
  vec.push_back("7");
  msgpack::sbuffer buffer;
  msgpack::pack(buffer, vec);

/*
  msgpack::type::tuple<int, bool, std::string> src(0, true, "example");
	msgpack::sbuffer buffer;
	msgpack::pack(buffer, src);
*/
	

	if ((numbytes = sendto(sockfd, (char*)buffer.data(), buffer.size(), 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		exit(1);
	}

	freeaddrinfo(servinfo);

	printf("talker: sent %d bytes to %s\n", numbytes, "localhost");

	close(sockfd);
	return 0;
}

	

// get sockaddr, IPv4 or IPv6:
void * kdht::get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// Start UDP listener 
int kdht::listen(std::string port)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
  msgpack::sbuffer buf;
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];

	// sets up first addrinfo struct
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, port.c_str(), &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("listener: bind");
			continue;
		}
		break;
	}
	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		return 2;
	}

	// done with servinfo, bound now
	freeaddrinfo(servinfo);

	printf("listener: waiting to recvfrom...\n");

	addr_len = sizeof their_addr;

  while(1) {
		// need to fix that hard coded 100
    if ((numbytes = recvfrom(sockfd, (char*)buf.data(), 100, 0,
      (struct sockaddr *)&their_addr, &addr_len)) == -1) {
      perror("recvfrom");
      exit(1);
    }

    printf("listener: got packet from %s\n",
    inet_ntop(their_addr.ss_family,
        get_in_addr((struct sockaddr *)&their_addr),
        s, sizeof s));
    
    msgpack::object_handle oh = msgpack::unpack(buf.data(),100);
    msgpack::object obj = oh.get();
    std::cout << obj << std::endl;
    std::vector<std::string> rvec;
    obj.convert(rvec);
    handle_function(rvec);
  }
	close(sockfd);
	return 0;
}

void kdht::handle_function(std::vector<std::string> argvec) {
  std::lock_guard<std::mutex> lck(storage_mtx);
  switch(stoi(argvec[0])) {
    case 0: rcv_q.emplace([=](){
              KVdisplay(argvec);
            });
    default: std::cout << "default\n";

 }
}

void kdht::KVdisplay(std::vector<std::string> argvec){
  for ( auto& arg : argvec ) {
    std::cout << "arg: " << arg << std::endl;
  }
}

