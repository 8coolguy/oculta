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

	int64 p,q;
	p = 17;
	q = 19;
	c = carmichaelFunction(p, q);
	cout << test(c,144) << "\t" << p << "\t" << q << endl;


	return 0;
}
