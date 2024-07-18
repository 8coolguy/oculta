#include "functions.hpp"
#include "types.hpp"
#include <iostream>


/*
*
*
*
*/
std::string test(int64 actual, int64 expected) {
	if (actual == expected) {
		return "PASS";
	} else {
		std::cout << actual << " != " << expected << std::endl;
		return "FAIL";
	}
}
std::string testStr(std::string actual, std::string expected) {
	if (actual == expected) {
		return "PASS";
	} else {
		std::cout << actual << " != " << expected << std::endl;
		return "FAIL";
	}
}
