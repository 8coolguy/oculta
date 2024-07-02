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
typedef uint8_t byte;
struct int48 {
	byte w0;
	byte w1;
	byte w2;
	byte w3;
	byte w4;
	byte w5;
} __attribute__((packed));

#endif
