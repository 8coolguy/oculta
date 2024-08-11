#include "functions.hpp"
#include "SymmetricEncryption.hpp"
#include "types.hpp"
#include "testing.hpp"
#include <iostream>

using namespace std;

int main(){
	cout << "AES Tests" << endl;
	SimpleAes aes;
	aes.setKey(0x3ba7);
	string s;
	cout <<	testStr(aes.decrypt(aes.encrypt("ok")),"ok") << endl;

	s = aes.encrypt("qw");
	s = aes.decrypt(s);
	cout << testStr(s, "qw") << endl;	


	return 0;
}
