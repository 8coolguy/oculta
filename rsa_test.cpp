/*
*
*
*
*
*
*
*
*/
#include <iostream>
#include "AsymmetricEncryption.hpp"
#include "types.hpp"
#include "testing.hpp"

using namespace std;

int main(){
	cout << "RSA Tests" << endl;
	Rsa rsa;
	string s;

	s = rsa.encrypt(rsa.e, "qweqweqweslkA", rsa.n);
	s = rsa.decrypt(s);
	cout << testStr(s, "qweqweqweslkA") << endl;	

	s = rsa.encrypt(rsa.e, "kA", rsa.n);
	s = rsa.decrypt(s);
	cout << testStr(s, "kA") << endl;	

	s = rsa.encrypt(rsa.e, "A", rsa.n);
	s = rsa.decrypt(s);
	cout << testStr(s, "A") << endl;

	s = rsa.encrypt(rsa.e, "N", rsa.n);
	s = rsa.decrypt(s);
	cout << testStr(s, "N") << endl;

	return 0;
}
