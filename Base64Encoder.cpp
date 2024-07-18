/*
*
*
*
*
*
*/
#include "SymmetricEncryption.hpp"


Base64Encoder::Base64Encoder() {
}
std::string Base64Encoder::encode(int64 message) {
	std::string res;
	for(int i = 0; i < 11; i++) {
		int64 temp = message & 0b111111;
		message = message >> 6;
		res += _base64Chars[temp];
	}
	return res;
}
int64 Base64Encoder::decode(std::string encodedMessage) {
	int64 res = 0;
	for(int i = 0; i < 11; i++) {
		int64 temp = _base64Chars.find(encodedMessage[i]);
		temp = temp << (6*i);
		res = res | temp;
	}
	return res;
}
