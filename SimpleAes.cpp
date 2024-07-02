/*
*
*
*
*
*
*
*/

#include "SymmetricEncryption.hpp"
#include "types.hpp"
#include <iostream>

byte SimpleAes::rcon(int i) {
	if(i==1) return byte(0b10000000);
	return byte(0b00110000);
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
	byte w0 = _key & 0xFF;
	byte w1 = (_key >> 8) & 0xFF;


	std::cout << "Original short number: " << std::hex << _key << std::endl;	    
	std::cout << "First 8 bits (LSB): " << std::hex << static_cast<int>(w0) << std::endl;
	std::cout << "Last 8 bits (MSB): " << std::hex << static_cast<int>(w1) << std::endl;


}
void SimpleAes::encrypt() {
	
	expandKey();
	
}
void SimpleAes::decrypt() {
	
}
