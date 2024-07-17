#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "types.hpp"

int64 gcd(int64 a, int64 b);
int64 inverse(int64 a, int64 b, int64 &x, int64 &y);
int64 forcePositive(int64 result, int64 p);
int64 carmichaelFunction(int64 a, int64 p);
int64 modularExponentiation(int64 base, int64 exponent, int64 mod);

#endif // 
