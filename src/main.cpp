#include <iostream>

#include "Rational.h"

using std::cout;
using std::cerr;
using std::endl;

using namespace rcd;

int main() {

	Rational r1(2, 4);
	cout << r1 << endl;

	Rational r2 = 3;
	cout << r2 << endl;

	Rational r3 = 0;
	cout << r3 << endl;

	Rational r5 = r1 * r2;
	cout << r5 << endl;

	cout << (Rational(5, 4) + 3) << endl;
	cout << (3 * Rational(1, 2)) << endl;

	try {
		Rational r4(3, 0); // should fail
	} catch (std::invalid_argument ia) {
		cerr << ia.what() << endl;
	}

	return 0;
}
