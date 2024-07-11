#ifndef ASYMMETRIC_ENCRYPTION_H
#define ASYMMETRIC_ENCRYPTION_H

#include <iostream>
#include "types.hpp"

class AsymmetricEncryption
{
protected:
	int8 _privateKey;
public:
	int8 _publicKey;
	AsymmetricEncryption();
	virtual void generateKeys();
	virtual std::string encrypt(int8 key,std::string message);
	virtual std::string decrypt(std::string cipherText);
};

class Rsa: public AsymmetricEncryption{
private:
	int8 _p;
	int8 _q;
	int8 _e;
	int8 _n;
public:
	Rsa();
	virtual void generateKeys();
	virtual std::string encrypt(int8	key,std::string message);
	virtual std::string decrypt(std::string cipherText);
};
#endif 
