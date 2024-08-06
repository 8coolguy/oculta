#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "types.hpp"

int64 gcd(int64 a, int64 b);
int64 inverse(int64 a, int64 b, int64 &x, int64 &y);
int64 forcePositive(int64 result, int64 p);
int64 carmichaelFunction(int64 a, int64 p);
int64 modularExponentiation(int64 base, int64 exponent, int64 mod);
std::string toString(int64 message);
int64 toInt(std::string message);

bool fermatsPrimeTest(int64 n, int64 a);
bool millerRabinTest(int64 n, int64 a);
#endif // 
