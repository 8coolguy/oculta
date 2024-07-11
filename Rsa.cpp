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
#include "functions.hpp"
#include <bitset>
#include "AsymmetricEncryption.hpp"

Rsa::Rsa() {
	std::srand(3);
	std::cout << "Rsa" << std::endl;
	_p = 13;
	_q = 17;
	_n = _p * _q;
	generateKeys();

	std::cout << "p = " << std::bitset<8>(_p) << std::endl << "q = " << std::bitset<8>(_q) << std::endl << "e = " << std::bitset<8>(_e) << std::endl << std::endl;
}
void Rsa::generateKeys() {
	// generate e
	_e = _p - 1;
	while(gcd(_e, (_p - 1) * (_q - 1)) != 1) {
		_e = std::rand() % ((_p - 1) * (_q - 1));	
	}
}
std::string Rsa::encrypt(int8 key,std::string message) {
	return message;
}
std::string Rsa::decrypt(std::string cipherText) {
	return cipherText;
}
