#pragma once //https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c
#ifndef NET_H
#define NET_H
#include "mongoose.h"

#if defined(HTTP_URL) && defined(HTTPS_URL)
#elif MG_ENABLE_TCPIP
#define HTTP_URL "http://0.0.0.0:80"     // Embedded build:
#define HTTPS_URL "https://0.0.0.0:443"  // Use standard privileged ports
#else
#define HTTP_URL "http://0.0.0.0:8000"    // Workstation build:
#define HTTPS_URL "https://0.0.0.0:8443"  // Use non-privileged ports
#endif

#define FS (&mg_fs_posix) 
#define ROOT_DIR "./web_root"

//Settings
//A admin user can configure admin settings which modify the:
//	-length of the password
//	-number of numbers
//	-number of other characters
//once the sets the settings, they can change it and previous users who registered will still be fine
struct settings{
	int length, numbers, others;
};

void net_init(struct mg_mgr *mgr, struct settings *s);

#endif // !NET



