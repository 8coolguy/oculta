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
	string s = rsa.encrypt(17, "A");
	s = rsa.decrypt(s);
	



	return 0;
}
