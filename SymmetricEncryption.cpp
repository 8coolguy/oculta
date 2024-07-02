/*
*
*
*
*
*
*
*/
#include <iostream>
#include "SymmetricEncryption.hpp"

SymmetricEncryption::SymmetricEncryption() {
	std::cout << "Symmetric Encryption" << std::endl;
}
void SymmetricEncryption::setKey(short key) {
	_key = key;
}

void SymmetricEncryption::encrypt() {
	std::cout << "Encrypt" << std::endl;
}

void SymmetricEncryption::decrypt() {
	std::cout << "Decrypt" << std::endl;
}
short SymmetricEncryption::getKey() {
	std::cout << "Get Key" << std::endl;
	return 0;
}
