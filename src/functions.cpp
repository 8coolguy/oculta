#include "functions.hpp"
#include "types.hpp"
#include <iostream>

/*
*
*
*
*/
int64 gcd(int64 a, int64 b){
	if(b > a) return gcd(b,a);
	if(a == b) return a;
	int64 c = a % b;
	if(c == 0) return b;
	return gcd(b,c);	
}

/*
*
*
*
*/
int64 inverse(int64 a, int64 p, int64 &x, int64 &y){
	if(gcd(a,p) != 1) return -1;
	if(a > p) return inverse(a % p , p, x, y);
	if(a == 0){
		x = 0;
		y = 1;
		return y;
	}
	if(p % a == 1){
		x = 1;
		y = -(p / a);
		return y;
	}
	inverse(p%a, a, x, y);
	int64 temp = y;
	y = x + (y * -(p/a));
	x = temp;
	return y;
}

/*
*
*
*
*/
int64 forcePositive(int64 result, int64 p){
	if(result < 0) return result + p;
	return result;
}

/*
*
*
*
*/
int64 carmichaelFunction(int64 p, int64 q){
	int64 result = (p - 1) * (q - 1);
	result = (result / gcd(p - 1, q - 1));
	return result;	
}

/*
*
*
*
*
*
*/
int64 modularExponentiation(int64 base, int64 exponent, int64 mod){
	int64 res = 1;
	base = base % mod;
	while(exponent > 0){
		if(exponent % 2 == 1){
			res = (res * base) % mod;
		}
		exponent = exponent >> 1;
		base = (base * base) % mod;
	}
	return res;
}

/*
*
*
*
*
*
*
*/
std::string toString(int64 message){

	std::string res;
	for(int i = 0; message > 0; i++) {
		res += char(message & 0x00000000000000ff);
		message = message >> 8;
	}
	return res;
}

int64 toInt(std::string message){
	int64 res = 0;
	for(int i = 0; i < message.size(); i++) {
		res = res | int64((char)message[i]) << (8*i);
	}
	return res;
}
