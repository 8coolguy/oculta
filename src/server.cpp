#include <iostream>
#include <string>
#include <vector>
#include "net.hpp"
#include "mongoose.h"   // To build, run: cc main.c mongoose.c

// HTTP server event handler function
static void run_mongoose(void) {
	struct mg_mgr mgr;
	mg_mgr_init(&mgr);
	mg_log_set(MG_LL_DEBUG);
	net_init(&mgr);
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
}
int main(void) {
	run_mongoose();	
	return 0;
}
