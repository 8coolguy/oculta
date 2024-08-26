#include "net.hpp"
#include "mongoose.h"
#include <stdio.h>
#include <pqxx/pqxx>

static void timer_sntp_fn(void* mgr) {  // SNTP timer function. Sync up time
	//mg_sntp_connect(mgr, NULL, NULL, NULL);
}

// Authenticated user.
// A user can be authenticated by:
//   - a name:pass pair, passed in a header Authorization: Basic .....
//   - an access_token, passed in a header Cookie: access_token=....
// When a user is shown a login screen, she enters a user:pass. If successful,
// a server responds with a http-only access_token cookie set.
struct user {
  const char *name, *pass, *access_token;
};

struct user *authenticate(struct mg_http_message *hm) {
	return NULL;
}

void sign_in(struct mg_http_message *hm, struct settings * s){
	
}

struct settings *retrieve_settings(pqxx::connection *conn) {

	return NULL;
}

void set_settings(struct settings *s, pqxx::connection *conn){
	pqxx::work work(*conn);

	work.exec("INSERT INTO settings (length, numbers, others) VALUES (" + std::to_string(s->length) + ", " + std::to_string(s->numbers) + ", " + std::to_string(s->others) + ")");
	work.commit();

}

void setup_database(pqxx::connection *conn) {
	pqxx::work work(*conn);

	work.exec("CREATE TABLE IF NOT EXISTS users (id SERIAL PRIMARY KEY, name TEXT, pass TEXT, access_token TEXT)");
	work.exec("CREATE TABLE IF NOT EXISTS settings (id SERIAL PRIMARY KEY, length INTEGER, numbers INTEGER, others INTEGER)");
	
	work.commit();
}

static void ev_handler(struct mg_connection *c, int ev, void *ev_data) {
	pqxx::connection cx{"dbname=postgres user=root password=root hostaddr=127.0.0.1 port=5432"};
	if( ev == MG_EV_ACCEPT){
	    if (c->fn_data != NULL) {  // TLS listener!
		struct mg_tls_opts opts = {0};
		opts.cert = mg_unpacked("/certs/server_cert.pem");
		opts.key = mg_unpacked("/certs/server_key.pem");
		mg_tls_init(c, &opts);
	    }

	}else if( ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		//struct user *u = authenticate(hm); 
		
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

void net_init(struct mg_mgr *mgr, struct settings *s){
	pqxx::connection cx{"dbname=postgres user=root password=root hostaddr=127.0.0.1 port=5432"};
	setup_database(&cx);
	set_settings(s, &cx);
	mg_http_listen(mgr, HTTP_URL, ev_handler, NULL);
	mg_http_listen(mgr, HTTPS_URL, ev_handler, (void*)1);
	mg_timer_add(mgr, 3600 * 1000, MG_TIMER_RUN_NOW | MG_TIMER_REPEAT, timer_sntp_fn, mgr);
}

