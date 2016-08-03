#include "infohash.h"


void Infohash::setRandom() {

  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(1, std::numeric_limits<uint8_t>::max());
  int rand_num = uniform_dist(e1);
  std::cout << "Random-number: " << rand_num << '\n';
	auto str = (unsigned char)rand_num;

	//printf("%02x \n",str);


  unsigned char hash[ID_BYTE_LENGTH]; // == 20

	//Do this correct, get rid of 8
  SHA1(&str, 8, hash);

//	std::cout << std::hex << hash << std::endl;
	///*
	for (int i = 0; i < ID_BYTE_LENGTH; i++) {
		this->ID[i] = hash[i];
 	  printf("%02x", ID[i]);
	}
	printf("\n\n");
	//*/

	//need to try with Infohash ID

}


