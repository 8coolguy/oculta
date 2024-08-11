/*
*
*
*
*
*
*
*/
#include <bitset>
#include "SymmetricEncryption.hpp"
#include "types.hpp"
#include "functions.hpp"
#include <iostream>
#include <string>

int8 SimpleAes::subNib(int8 b) {
	int8 n0 = b & 0x0f;
	int8 n1 = b >> 4;
	n0 = _sbox[n0];
	n1 = _sbox[n1];
	b = (n1 << 4) | n0;
	return b;
}
int8 SimpleAes::invSubNib(int8 b) {
	int8 n0 = b & 0x0f;
	int8 n1 = b >> 4;
	n0 = _sboxInverse[n0];
	n1 = _sboxInverse[n1];
	b = (n1 << 4) | n0;
	return b;
}
int8 rotNib(int8 b) {
	int8 n0 = b & 0x0f;
	int8 n1 = b >> 4;
	return (n0 << 4) | n1;
}

int8 rcon(int i) {
	if(i==1) return 0b10000000;
	return 0b00110000;
}

SimpleAes::SimpleAes() { 
	_key = getKey();

}

short SimpleAes::getKey() {
	if(_key > 0)
		return _key;
	return 0;
}

struct int48 SimpleAes::expandKey(){
	int8 w0 = _key & 0xFF;
	int8 w1 = (_key >> 8) & 0xFF;

	int8 w2 = w0 ^ rcon(1) ^ subNib(rotNib(w1));
	int8 w3 = w2 ^ w1;

	int8 w4 = w2 ^ rcon(2) ^ subNib(rotNib(w3));
	int8 w5 = w4 ^ w3;

	struct int48 key = {w0, w1, w2, w3, w4, w5};

//	std::cout << std::bitset<8>(key.w0) << std::endl;
//	std::cout << std::bitset<8>(key.w1) << std::endl;
//	std::cout << std::bitset<8>(key.w2) << std::endl;
//	std::cout << std::bitset<8>(key.w3) << std::endl;
//	std::cout << std::bitset<8>(key.w4) << std::endl;
//	std::cout << std::bitset<8>(key.w5) << std::endl;
	
	return key;
}
void shiftRow(int8&b1, int8&b2) {
	int8 n1 = b1 & 0x0f;
	int8 n2 = b1 >> 4;
	int8 n3 = b2 & 0x0f;
	int8 n4 = b2 >> 4;
	b1 = (n2 << 4) | (n3 << 0);
	b2 = (n4 << 4) | (n1 << 0);
}
int8 mixCol(int8 b) {

	int8 c;
	int8 seven = b >> 0 & 1;
	int8 six = b >> 1 & 1;
	int8 five = b >> 2 & 1;
	int8 four = b >> 3 & 1;
	int8 three = b >> 4 & 1;
	int8 two = b  >> 5 & 1;
	int8 one = b >> 6 & 1;
	int8 zero = b >> 7 & 1;

	c = 
		(six ^ zero) << 7 |
		(four ^ one ^ seven) << 6 |
		(four ^ two ^ five) << 5 |
		(three ^ five) << 4 |
		(two ^ four) << 3 |
		(zero ^ five ^ three) << 2 |
		(one ^ zero ^ six) << 1 |
		(seven ^ one) << 0;
		

	return c;
}
int8 invMixCol(int8 b) {

	int8 c;
	int8 seven = b >> 0 & 1;
	int8 six = b >> 1 & 1;
	int8 five = b >> 2 & 1;
	int8 four = b >> 3 & 1;
	int8 three = b >> 4 & 1;
	int8 two = b  >> 5 & 1;
	int8 one = b >> 6 & 1;
	int8 zero = b >> 7 & 1;

	int8 temp4 = one ^ seven;
	int8 temp1 = zero ^ six;
	int8 temp0 = three ^ five;
	int8 temp5 = two ^ four;

	int8 temp2 = two ^ temp4 ^ temp5;
	int8 temp3 = three ^ temp5;
	int8 temp6 = zero ^ temp0;
	int8 temp7 = seven ^ temp1;
	c = 
		(temp0) << 7 |
		(temp1) << 6 |
		(temp2) << 5 |
		(temp3) << 4 |
		(temp4) << 3 | 
		(temp5) << 2 |
		(temp6) << 1 |
		(temp7) << 0;
		

	return c;
}
std::string SimpleAes::encrypt(std::string message) {
	Base64Encoder encoder;
	if(message.size()!=2) return std::string();
	struct int48 key = expandKey();
	
	int8 temp0 = int8((char)message[0]);
	int8 temp1 = int8((char)message[1]);

	temp0 = temp0 ^ key.w0;
	temp1 = temp1 ^ key.w1;

	temp0 = subNib(temp0);
	temp1 = subNib(temp1);

	shiftRow(temp0, temp1);

	temp0 = mixCol(temp0);
	temp1 = mixCol(temp1);
	
	temp0 = temp0 ^ key.w2;
	temp1 = temp1 ^ key.w3;

	temp0 = subNib(temp0);
	temp1 = subNib(temp1);

	shiftRow(temp0, temp1);
	
	temp0 = temp0 ^ key.w4;
	temp1 = temp1 ^ key.w5;

	int64 temp = int64(temp0) | (int64(temp1) << 8);

	std::string res = encoder.encode(temp);

	//std::cout <<"Cipher Text: "<< temp << std::endl;
	//std::cout <<"Cipher Text: "<< res << std::endl;
	//std::cout <<"Cipher Text: "<< encoder.decode(res) << std::endl;
	
	return res;

}
std::string SimpleAes::decrypt(std::string cipherText) {
	if(cipherText.size()==2) return std::string();
	Base64Encoder encoder;
	int64 cipher = encoder.decode(cipherText);

	int8 temp0 = int8(cipher & 0xff);
	int8 temp1 = int8((cipher >> 8) & 0xff);
	
	//std::cout << std::bitset<8>(temp0) << std::endl << std::bitset<8>(temp1) << std::endl;
	
	struct int48 key = expandKey();

	temp0 = temp0 ^ key.w4;
	temp1 = temp1 ^ key.w5;

	shiftRow(temp0, temp1);

	temp0 = invSubNib(temp0);
	temp1 = invSubNib(temp1);

	temp0 = temp0 ^ key.w2;
	temp1 = temp1 ^ key.w3;

	temp0 = invMixCol(temp0);
	temp1 = invMixCol(temp1);

	shiftRow(temp0, temp1);

	temp0 = invSubNib(temp0);
	temp1 = invSubNib(temp1);

	temp0 = temp0 ^ key.w0;
	temp1 = temp1 ^ key.w1;

	int64 temp = int64(temp0) | (int64(temp1) << 8);
	return toString(temp);	
}
