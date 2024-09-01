#include "net.hpp"
#include "mongoose.h"
#include <cstring>
#include <iomanip>
#include <pqxx/result.hxx>
#include <pqxx/strconv.hxx>
#include <stdio.h>
#include <iostream>
#include <pqxx/pqxx>
#include <chrono>
#include <boost/algorithm/string.hpp>

static mg_sha1_ctx ctx;

static void timer_sntp_fn(void* mgr) {  // SNTP timer function. Sync up time
	//mg_sntp_connect(mgr, NULL, NULL, NULL);
}

bool valid_timestamp(std::string timestamp, int token_duration) {
	std::tm tm;
	std::stringstream ss(timestamp);
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	//convert to time_point
	std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
	
	tp += std::chrono::seconds(token_duration);

	// Convert back to std::time_t
	std::time_t new_time = std::chrono::system_clock::to_time_t(tp);
	//get current time into time_t
	std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	if (new_time < current_time) {
		return false;
	}

	return true;
}

std::string authenticate(struct mg_http_message *hm, pqxx::connection *conn, int user_id) {
	pqxx::work work(*conn);
	pqxx::result result = work.exec("SELECT MD5(random()::text);");
	std::string token = result[0][0].as<std::string>();
	work.exec("INSERT INTO authenticated (user_id, access_token) VALUES (" + std::to_string(user_id) + ", '" + token + "')");
	work.commit();
	return token;
}

void handle_logout(struct mg_connection *c) {
	char cookie[256];
	mg_snprintf(cookie, sizeof(cookie),
	      "Set-Cookie: access_token=; Path=/; "
	      "Expires=Thu, 01 Jan 1970 00:00:00 UTC; "
	      "%sHttpOnly; Max-Age=0; \r\n",
	      c->is_tls ? "Secure; " : "");
	mg_http_reply(c, 200, cookie, NULL);
}

struct settings retrieve_settings(pqxx::connection *conn) {

	pqxx::work work(*conn);
	struct settings s;
	pqxx::result result = work.exec("SELECT * FROM settings WHERE id = 1");
	for (auto row: result) {
		s.length = row[1].as<int>();
		s.numbers = row[2].as<int>();
		s.others = row[3].as<int>();
		s.capitals = row[4].as<int>();
		s.token_duration = row[5].as<int>();
	}

	work.commit();
	return s;
}
void verify_authentication(struct mg_connection *c, struct mg_http_message *hm, pqxx::connection *conn) {
	pqxx::work work(*conn);
	struct mg_str *cookie = mg_http_get_header(hm, "Cookie");
	struct mg_str access_token = mg_str("");

	if (cookie == NULL) {
		mg_http_reply(c, 400, NULL, "Not authenticated\n");
		return;
	}
	access_token = mg_http_get_header_var(*cookie, mg_str("access_token"));

	std::string token = std::string(access_token.buf);
	boost::trim_right(token);
 	pqxx::result result = work.exec("SELECT * FROM authenticated WHERE access_token = '" + token + "'");
	work.commit();
	//1. Need to check if token is valid
	//2. Check if access token is still within token_duration
	if(result.size() == 0){
		mg_http_reply(c, 400, NULL, "Invalid access token\n");
		return;
	}
	struct settings s = retrieve_settings(conn);

	for (auto row: result) {
		std::string timestamp = row[1].as<std::string>();
		if(!valid_timestamp(timestamp, s.token_duration)){
			mg_http_reply(c, 400, NULL, "Invalid access token\n");
			return;
		}
	}

	mg_http_reply(c, 200, NULL, "Authenticated");

}
void handle_login(struct mg_http_message *hm, mg_connection * c, struct settings * s, pqxx::connection *conn){
	char user[256],pass[256],hash[32],cookie[256];
	unsigned char buf[20];
	int user_id;
	std::string dbhash, token;	
	mg_http_creds(hm, user, sizeof(user), pass, sizeof(pass));
	pqxx::work work(*conn);
	pqxx::result result = work.exec("SELECT * FROM users WHERE name = '" + std::string(user) + "'");
	work.commit();
	
	if(result.size() == 0){
		mg_http_reply(c, 400, NULL, "User does not exist\n");
		return;
	}
	for (auto row: result) {
		user_id = row[0].as<int>();
		dbhash = row[2].as<std::string>();
	}

	mg_sha1_init(&ctx);
	mg_sha1_update(&ctx, (unsigned char*) pass, strlen(pass));
	mg_sha1_final(buf, &ctx);
	mg_base64_encode(buf,20,hash,32);
	if(strcmp(dbhash.c_str(), hash) != 0){
		mg_http_reply(c, 400, NULL, "Password incorrect\n");
		return;
	}
	token = authenticate(hm, conn, user_id);
	mg_snprintf(cookie, sizeof(cookie),
	      "Set-Cookie: access_token=%s; Path=/; "
	      "%sHttpOnly; SameSite=Lax; Max-Age=%d\r\n",
	      token.c_str(), c->is_tls ? "Secure; " : "", s->token_duration);
	mg_http_reply(c, 200, cookie, "{%m:%m}", MG_ESC("user"), MG_ESC(user));
}

void handle_signup(struct mg_http_message *hm, mg_connection * c,struct settings * s, pqxx::connection *conn){
	pqxx::work work(*conn);
	char *user, *pass, *pass2, *hash;
	unsigned char buf[20];
	int numbers = 0, others = 0,capitals = 0;
	user = mg_json_get_str(hm->body, "$.username");
	pqxx::result result = work.exec("SELECT * FROM users WHERE name = '" + std::string(user) + "'");
	if(result.size() > 0){
		mg_http_reply(c, 400, NULL, "User already exists\n");
		return;
	}
	pass = mg_json_get_str(hm->body, "$.password");
	if(strlen(pass) < s->length){
		mg_http_reply(c, 400, NULL, "Password too short\n");
		return;
	}
	
	for( int i = 0; i < strlen(pass); i++){
		if(pass[i] >= '0' && pass[i] <= '9'){
			numbers++;	
		}	
		if (pass[i] >= 'a' && pass[i] <= 'z')
			others++;
		if (pass[i] >= 'A' && pass[i] <= 'Z')
			capitals++;	
	}
	if(numbers < s->numbers){
		mg_http_reply(c, 400, NULL, "Not enough numbers\n");
		return;
	}
	if(strlen(pass) - capitals - numbers - others < s->others){
		mg_http_reply(c, 400, NULL, "Not enough other characters\n");
		return;
	}
	if(capitals < s->capitals){
		mg_http_reply(c, 400, NULL, "Not enough capitals\n");
		return;
	}

	pass2 = mg_json_get_str(hm->body, "$.password2");
	if(strcmp(pass, pass2) != 0){
		mg_http_reply(c, 400, NULL, "Passwords don't match\n");
		return;
	}
	mg_sha1_init(&ctx);
	mg_sha1_update(&ctx, (unsigned char*) pass, strlen(pass));
	mg_sha1_final(buf, &ctx);
	mg_base64_encode(buf,20,hash,32);

	work.exec("INSERT INTO users (name, pass) VALUES ('" + std::string(user) + "', '" + std::string(hash)+ "')");
	work.commit();

	mg_http_reply(c, 200, NULL, "true\n");
	MG_VERBOSE(("user [%s] pass [%s]", user, pass));
}

void set_settings(struct settings *s, pqxx::connection *conn){
	pqxx::work work(*conn);

	work.exec("INSERT INTO settings (length, numbers, others, capitals, token_duration) VALUES (" + std::to_string(s->length) + ", " + std::to_string(s->numbers) + ", " + std::to_string(s->others) + ", " + std::to_string(s->capitals) + ", " + std::to_string(s->token_duration) + ")");
	work.commit();
}

void setup_database(pqxx::connection *conn) {
	pqxx::work work(*conn);
	work.exec("DROP TABLE IF EXISTS settings");
	work.exec("DROP TABLE IF EXISTS users CASCADE");
	work.exec("DROP TABLE IF EXISTS authenticated");
	work.exec("CREATE TABLE IF NOT EXISTS users (id SERIAL PRIMARY KEY, name TEXT, pass TEXT )");
	work.exec("CREATE TABLE IF NOT EXISTS settings (id SERIAL PRIMARY KEY, length INTEGER, numbers INTEGER, others INTEGER, capitals INTEGER, token_duration INTEGER)");
	work.exec("CREATE TABLE IF NOT EXISTS authenticated (id SERIAL PRIMARY KEY, date TIMESTAMP DEFAULT CURRENT_TIMESTAMP, user_id INTEGER REFERENCES users(id), access_token TEXT UNIQUE)");
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
		struct settings s = retrieve_settings(&cx);
		if (mg_match(hm->uri, mg_str("/api/login"), NULL)) {
			handle_login(hm, c, &s, &cx);
		}
		else if (mg_match(hm->uri, mg_str("/api/signup"), NULL)) {
			handle_signup(hm, c, &s, &cx);
		}
		else if (mg_match(hm->uri, mg_str("/api/logout"), NULL)) {
			handle_logout(c);
		}
		else if (mg_match(hm->uri, mg_str("/home"), NULL)) {
			verify_authentication(c, hm, &cx);
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

