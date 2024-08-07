#include "functions.hpp"
#include "types.hpp"
#include "testing.hpp"
#include <iostream>

using namespace std;

int main(){
	cout << "GCD Tests" << endl;
	int64 c = gcd(12, 4);
	cout << test(c,4) << "\t" << 12 << "\t" << 4 << endl;

	c = gcd(12, 7);
	cout << test(c,1) << "\t" << 12 << "\t" << 7 << endl;

	c = gcd(2, 7);
	cout << test(c,1) << "\t" << 2 << "\t" << 7 << endl;

	c = gcd(2134, 712412);
	cout << test(c,2) << "\t" << 2134 << "\t" << 712412 << endl;

	c = gcd(2134849231, 712412342);
	cout << test(c,1) << "\t" << 2134849231 << "\t" <<  712412342 << endl;

	cout << "Inverse Tests" << endl;

	int64 x,y;
	x = 1;
	y = 1;
	c = forcePositive(inverse(19, 17, x, y), 17);
	cout << test(c,9) << "\t" << 19 << "\t" << 17 << endl;

	c = forcePositive(inverse(29, 42, x, y), 42);
	cout << test(c,29) << "\t" << 29 << "\t" << 42 << endl;

	c = forcePositive(inverse(3123123123, 2623423423,x, y), 2623423423);
	cout << test(c,1639639642) << "\t" << 3123123123 << "\t" << 2623423423 << endl;

	cout << "Carmichael Tests" << endl;

	int64 p,q;
	p = 17;
	q = 19;
	c = carmichaelFunction(p, q);
	cout << test(c,144) << "\t" << p << "\t" << q << endl;

	cout << "Fermats Prime Tests" << endl;

	c = fermatsPrimeTest(17, 5);
	cout << test(c,1) << "\t" << 17 << "\t" << 5 << endl;

	c = fermatsPrimeTest(6, 5);
	cout << test(c,0) << "\t" << 6 << "\t" << 5 << endl;

	c = fermatsPrimeTest(221, 38);
	cout << test(c,1) << "\t" << 221 << "\t" << 38 << endl;

	c = fermatsPrimeTest(221, 24);
	cout << test(c,0) << "\t" << 221 << "\t" << 24 << endl;

	
	cout << "Miller Rabin Prime Tests" << endl;

	c = millerRabinTest(17, 5);
	cout << test(c,1) << "\t" << 17 << "\t" << 5 << endl;

	c = millerRabinTest(6, 5);
	cout << test(c,0) << "\t" << 6 << "\t" << 5 << endl;

	c = millerRabinTest(221, 174);
	cout << test(c,1) << "\t" << 221 << "\t" << 174 << endl;

	c = millerRabinTest(221, 137);
	cout << test(c,0) << "\t" << 221 << "\t" << 137 << endl;

	cout << "Miller Rabin Amplification Prime Tests" << endl;

	c = millerRabinAmplify(43);
	cout << test(c,1) << "\t" << 43 << endl;

	c = millerRabinAmplify(6);
	cout << test(c,0) << "\t" << 6 << endl;

	c = millerRabinAmplify(221);
	cout << test(c,0) << "\t" << 221 << endl;

	c = millerRabinAmplify(77213);
	cout << test(c,1) << "\t" << 77213 << endl;
	
	c = millerRabinAmplify(8114696549);
	cout << test(c,1) << "\t" << 8114696549 << endl;

	c = millerRabinAmplify(3213003161);
	cout << test(c,1) << "\t" << 3213003161 << endl;

	c = millerRabinAmplify(44077973);
	cout << test(c,1) << "\t" << 44077973 << endl;

	c = millerRabinAmplify(822518149);
	cout << test(c,1) << "\t" << 822518149 << endl;

	c = millerRabinAmplify(754146623);
	cout << test(c,1) << "\t" << 754146623 << endl;

	c = millerRabinAmplify(506669291);
	cout << test(c,1) << "\t" << 506669291 << endl;

	c = millerRabinAmplify(9160068971);
	cout << test(c,1) << "\t" << 9160068971 << endl;

	c = millerRabinAmplify(1010012683);
	cout << test(c,1) << "\t" << 1010012683 << endl;

	c = millerRabinAmplify(2893922039);
	cout << test(c,1) << "\t" << 2893922039 << endl;

	c = millerRabinAmplify(293049567887437);
	cout << test(c,1) << "\t" << 293049567887437 << endl;

	c = millerRabinAmplify(100363750742395471);
	cout << test(c,1) << "\t" << 100363750742395471 << endl;

	cout << "Manual Prime Tests" << endl;
	
	cout << generatePrime() << endl;
	cout << generatePrime() << endl;
	cout << generatePrime() << endl;
	cout << generatePrime() << endl;
	cout << generatePrime() << endl;
	cout << generatePrime() << endl;
	cout << generatePrime() << endl;
	cout << generatePrime() << endl;
	cout << generatePrime() << endl;
	cout << generatePrime() << endl;

	random64bit(); 

	return 0;
}
