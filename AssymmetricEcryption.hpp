#ifndef ASSYMMETRICECIPHER_H
#define ASSYMMETRICECIPHER_H



class AssymetricEcryption
{
public:
	AssymetricEcryption();
	virtual void generateKeys();
	virtual std::string encrypt(int8 key,std::string message);
	virtual std::string decrypt(std::string cipherText);
};

class Rsa
{
public:
	Rsa();
};

#endif 
