#include <iostream>
#include <string>
#include <vector>
#include "net.hpp"
#include "mongoose.h"   // To build, run: cc main.c mongoose.c


// HTTP server event handler function
static void run_mongoose(struct settings *s) {
	struct mg_mgr mgr;
	mg_mgr_init(&mgr);
	mg_log_set(MG_LL_DEBUG);
	net_init(&mgr,s);
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
}
int main(int argc, char *argv[]) {
	struct settings s;
	s.length = 8;
	s.numbers = 1;
	s.others = 1;
	s.capitals = 1;
	s.token_duration = 86400;
	for(int i =1; i < argc; i+=2) {
		if(strcmp(argv[i], "--password_length") == 0) {
			s.length = std::stoi(argv[i+1]);
		}
		else if(strcmp(argv[i], "--numbers") == 0) {
			s.numbers = std::stoi(argv[i+1]);
		} 
		else if(strcmp(argv[i], "--others") == 0) {
			s.others = std::stoi(argv[i+1]);
		}
		else if (strcmp(argv[i], "--capitals") == 0) {
			s.capitals = std::stoi(argv[i+1]);
		}else if(strcmp(argv[i], "--token_duration") == 0) {
			s.token_duration = std::stoi(argv[i+1]);	
		}
		else if(strcmp(argv[i], "--help") == 0) {
			std::cout << "Usage: ./server --password_length <length> --numbers <numbers> --others <others> --capitals <capitals> --token_duration <token_duration>" << std::endl;
			return 0;
		}
	}
	std::cout << "Password Settings: " << s.length << " " << s.numbers << " " << s.others << " " << s.capitals << " " << s.token_duration << std::endl;
	run_mongoose(&s);	
	return 0;
}
