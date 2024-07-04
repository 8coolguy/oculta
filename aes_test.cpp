#include "functions.hpp"
#include "SymmetricEncryption.hpp"
#include "types.hpp"
#include "testing.hpp"
#include <iostream>

using namespace std;

int main(){
	cout << "AES Tests" << endl;
	SimpleAes aes;
	aes.setKey(0x3BA7);
	aes.encrypt("This is the message");

	return 0;
}
