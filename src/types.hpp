/*
*
*
*
*
*
*
*
*
*
*
*
*/

#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>
#include <cstdint>

typedef long long int int64;
typedef uint8_t int8;
typedef __int128 int128;
struct int48 {
	int8 w0;
	int8 w1;
	int8 w2;
	int8 w3;
	int8 w4;
	int8 w5;
} __attribute__((packed));

#endif
