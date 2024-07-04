/*
*
*
*
*
*
*
*/

#include "SymmetricEncryption.hpp"
#include "types.hpp"
#include <iostream>

int8 SimpleAes::subNib(int8 b) {
	int8 n0 = b & 0x0f;
	int8 n1 = b >> 4;
	n0 = _sbox[n0];
	n1 = _sbox[n1];
	b = (n1 << 4) | n0;
	return b;
}
int8 rotNib(int8 b) {
	int8 n0 = b & 0x0f;
	int8 n1 = b >> 4;
	return (n0 << 4) | n1;
}

int8 rcon(int i) {
	if(i==1) return 0b10000000;
	return 0b00110000;
}

SimpleAes::SimpleAes() { 
	_key = getKey();

}

short SimpleAes::getKey() {
	if(_key > 0)
		return _key;
	return 0;
}

struct int48 SimpleAes::expandKey(){
	int8 w0 = _key & 0xFF;
	int8 w1 = (_key >> 8) & 0xFF;

	int8 w2 = w0 ^ rcon(1) ^ subNib(rotNib(w1));
	int8 w3 = w2 ^ w1;

	int8 w4 = w2 ^ rcon(2) ^ subNib(rotNib(w3));
	int8 w5 = w4 ^ w3;

	struct int48 key = {w0, w1, w2, w3, w4, w5};

	std::cout << "Original short number: " << std::hex << _key << std::endl;	    
	std::cout << "W0 " << std::hex << static_cast<int>(w0) << std::endl;
	std::cout << "W1 " << std::hex << static_cast<int>(w1) << std::endl;
	std::cout << "W2 " << std::hex << static_cast<int>(w2) << std::endl;
	std::cout << "W3 " << std::hex << static_cast<int>(w3) << std::endl;
	std::cout << "W4 " << std::hex << static_cast<int>(w4) << std::endl;
	std::cout << "W5 " << std::hex << static_cast<int>(w5) << std::endl;
	return key;

}
void SimpleAes::encrypt(std::string message) {
	if(message.size()!=2) return;	
	struct int48 key = expandKey();
	






	
}
void SimpleAes::decrypt() {
	
}

