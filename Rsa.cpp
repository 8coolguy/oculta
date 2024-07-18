/*
*
*
*
*
*
*
*
*/
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <cassert>
#include "AsymmetricEncryption.hpp"
#include "SymmetricEncryption.hpp"
#include "functions.hpp"

Rsa::Rsa() {
	std::srand(3);
	std::cout << "Rsa" << std::endl;
	_p = 61;
	_q = 53;
	_n = _p * _q;
	generateKeys();
	std::cout << "p = " << _p << std::endl << "q = " << _q << std::endl;
	std::cout << "n = " << _n << std::endl << "d = " << _d << std::endl;
	std::cout << "e = " << _e << std::endl;
}
void Rsa::generateKeys() {
	// generate e
	_e = _p - 1;
	int64 ln = carmichaelFunction(_p, _q);
	std::cout << "ln = " << (int)ln << std::endl;

	while(gcd(_e, ln) != 1) {
		_e = std::rand() % ln;
	}
	_e = 17;
	// generate d
	int64 x,y;
	_d = forcePositive(inverse(_e, ln,x, y),ln);
}
std::string Rsa::encrypt(int64 key,std::string message) {
	Base64Encoder encoder;
	assert(message.size() < 9);
	int64 res =0;
	for(int i = 0; i < message.size(); i++) {
		res = res | int64((char)message[i]) << (8*i);
	}
	res = modularExponentiation(res, _e, _n);
	std::cout << res << std::endl;
	std::string resStr = encoder.encode(res);

	std::cout << resStr << std::endl;
	return resStr;
}
std::string Rsa::decrypt(std::string cipherText) {
	assert(cipherText.size() < 12);
	Base64Encoder decoder;
	int64 res = decoder.decode(cipherText);
	std::cout << res << std::endl;
	res = modularExponentiation(res, _d, _n);
	std::string resStr = toString(res);
	return resStr;
}
