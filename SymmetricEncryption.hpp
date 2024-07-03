/*
*
*
*
*
*
*
*/

#include "types.hpp"

#ifndef SYMMETRIC_ENCRYPTION_HPP
#define SYMMETRIC_ENCRYPTION_HPP

class SymmetricEncryption
{
protected:
	short _key;
public:
	SymmetricEncryption();
	virtual void encrypt();
	virtual void decrypt();
	virtual short getKey();
	void setKey(short key);
};

class SimpleAes: public SymmetricEncryption{
private:
	int8 _sbox[16] = { 9, 4, 10, 11, 13, 1, 8, 5, 6, 2, 0, 3, 12, 14, 15, 7 };
	struct int48 expandKey();
	int8 subNib(int8 b);
public:
	SimpleAes();
	virtual void encrypt();
	virtual void decrypt();
	virtual short getKey();

};
#endif // !SYMME
