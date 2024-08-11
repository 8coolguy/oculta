/*
*
*
*
*
*
*
*/

#include "types.hpp"
#include <iostream>

#ifndef SYMMETRIC_ENCRYPTION_HPP
#define SYMMETRIC_ENCRYPTION_HPP

class SymmetricEncryption
{
protected:
	short _key;
public:
	SymmetricEncryption();
	virtual std::string encrypt(std::string message);
	virtual std::string decrypt(std::string message);
	virtual short getKey();
	void setKey(short key);
};

class SimpleAes: public SymmetricEncryption{
private:
	int8 _sbox[16] = { 9, 4, 10, 11, 13, 1, 8, 5, 6, 2, 0, 3, 12, 14, 15, 7 };
	int8 _sboxInverse[16] = { 10, 5, 9, 11, 1, 7, 8, 15, 6, 0, 2, 3, 12, 4, 13, 14};
	struct int48 expandKey();
	int8 subNib(int8 b);
	int8 invSubNib(int8 b);
public:
	SimpleAes();
	virtual std::string encrypt(std::string message);
	virtual std::string decrypt(std::string message);
	virtual short getKey();

};

class Base64Encoder{
private:
	std::string _base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	
public:
	Base64Encoder();
	std::string encode(int64 message);
	int64 decode(std::string encodedMessage);
};
#endif // !SYMME
