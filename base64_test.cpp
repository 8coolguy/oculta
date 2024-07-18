/*
*
*
*
*
*
*
*/
#include <iostream>
#include "testing.hpp"
#include "SymmetricEncryption.hpp"
#include "functions.hpp"

using namespace std;

int main(){
	cout << "Base64 Tests" << endl;
	Base64Encoder encoder;
	cout << testStr("k5WQAAAAAAA",encoder.encode((int64)(0x416E64))) << endl;
	cout << test(0x4f4f53494e4550, encoder.decode(encoder.encode((int64)(0x4f4f53494e4550))))<< endl;
	cout << testStr("PENISOO", toString((int64)(0x4F4F53494E4550))) << endl;
	cout << test(0x4f4f53494e4550, toInt("PENISOO"))<< endl;
	return 0;
}
