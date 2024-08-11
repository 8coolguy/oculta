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

std::string SymmetricEncryption::encrypt(std::string message) {
	std::cout << "Encrypt" << std::endl;
}

std::string SymmetricEncryption::decrypt(std::string cipherText) {
	std::cout << "Decrypt" << std::endl;
}
short SymmetricEncryption::getKey() {
	std::cout << "Get Key" << std::endl;
	return 0;
}
