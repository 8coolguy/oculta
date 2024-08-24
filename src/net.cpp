#include "net.hpp"
#include "mongoose.h"
#include <stdio.h>

static void timer_sntp_fn(void* mgr) {  // SNTP timer function. Sync up time
	//mg_sntp_connect(mgr, NULL, NULL, NULL);
}

static void ev_handler(struct mg_connection *c, int ev, void *ev_data) {
	if( ev == MG_EV_ACCEPT){
	    if (c->fn_data != NULL) {  // TLS listener!
		struct mg_tls_opts opts = {0};
		opts.cert = mg_unpacked("/certs/server_cert.pem");
		opts.key = mg_unpacked("/certs/server_key.pem");
		mg_tls_init(c, &opts);
	    }
	}else if( ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		
		if (mg_match(hm->uri, mg_str("/api/login"), NULL)) {
			printf("Cream\n");
		}
		else if (mg_match(hm->uri, mg_str("/api/signin"), NULL)) {
			printf("Cream\n");
		}
		else if (mg_match(hm->uri, mg_str("/api/public"), NULL)) {
			printf("Cream\n");
		}
		else{
			struct mg_http_serve_opts opts;
			memset(&opts, 0, sizeof(opts));
			opts.fs = FS;
			opts.root_dir = ROOT_DIR;
			mg_http_serve_dir(c, hm, &opts);
		}

		MG_DEBUG(("%lu %.*s %.*s -> %.*s", c->id, (int) hm->method.len,
			hm->method.buf, (int) hm->uri.len, hm->uri.buf, (int) 3,
			&c->send.buf[9]));
	}
}

void net_init(struct mg_mgr *mgr){
	mg_http_listen(mgr, HTTP_URL, ev_handler, NULL);
	mg_http_listen(mgr, HTTPS_URL, ev_handler, (void*) 1);
	mg_timer_add(mgr, 3600 * 1000, MG_TIMER_RUN_NOW | MG_TIMER_REPEAT, timer_sntp_fn, mgr);
}

