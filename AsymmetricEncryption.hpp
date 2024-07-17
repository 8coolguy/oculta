#ifndef ASYMMETRIC_ENCRYPTION_H
#define ASYMMETRIC_ENCRYPTION_H

#include <iostream>
#include "types.hpp"

class AsymmetricEncryption
{
public:
	AsymmetricEncryption();
	virtual void generateKeys();
	virtual std::string encrypt(int64 key,std::string message);
	virtual std::string decrypt(std::string cipherText);
};

class Rsa: public AsymmetricEncryption{
private:
	int64 _p;
	int64 _q;
	int64 _e;
	int64 _n;
	int64 _d;
public:
	Rsa();
	virtual void generateKeys();
	virtual std::string encrypt(int64 key,std::string message);
	virtual std::string decrypt(std::string cipherText);
};
#endif 
