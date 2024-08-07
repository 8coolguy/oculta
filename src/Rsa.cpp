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

#define SIZEPERCHAR 11

Rsa::Rsa() {
	std::srand(3);
	std::cout << "Rsa" << std::endl;
	_p = 1381;
	_q = 1453;
	_p = generatePrime();
	_q = generatePrime();
	n = _p * _q;
	generateKeys();
	std::cout << "p = " << _p << std::endl << "q = " << _q << std::endl;
	std::cout << "n = " << n << std::endl << "d = " << _d << std::endl;
	std::cout << "e = " << e << std::endl;
}
/*
* Genreates public and private keys. Uses Sieve of Eratosthenes algorithm to
* gernerate prime numbers for the keys. Randomly generates e.
*
*
*/
void Rsa::generateKeys() {
	// generate e
	e = _p - 1;
	

	int64 ln = carmichaelFunction(_p, _q);
	std::cout << "ln = " << (int64)ln << std::endl;

	while(gcd(e, ln) != 1) {
		e= std::rand() % ln;
	}
	// generate d
	int64 x,y;
	_d = forcePositive(inverse(e, ln,x, y),ln);
}
std::string Rsa::encrypt(int64 key,std::string message, int64 mod) {

	Base64Encoder encoder;
	std::string resStr;
	for(int i = 0; i < message.size(); i++) {
		int64 res = char(message[i]);
		res = modularExponentiation(res, key, mod);
		resStr += encoder.encode(res);
	}
	return resStr;
}

std::string Rsa::decrypt(std::string cipherText) {
	Base64Encoder decoder;
	std::string resStr;
	for(int i = 0; i < cipherText.size()/SIZEPERCHAR; i++) {
		int64 res = decoder.decode(cipherText.substr(i*SIZEPERCHAR, SIZEPERCHAR));
		res = modularExponentiation(res, _d, n);
		resStr += toString(res);
	}
	return resStr;
}
