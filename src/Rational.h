/*
 * Rational.h
 *
 *  Created on: 2010-12-09
 *      Author: cdunphy
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <cstdlib>
#include <ostream>
#include <string>
#include <sstream>
#include <stdexcept>

namespace rcd {

/*
 * This class represents a rational number in C++.  This is a header only
 * implementation because I inlined all of the functions (they are small)
 * to optimize (hopefully?) performance.
 */
class Rational {
	friend std::ostream& operator<<(std::ostream& out, const Rational& r);
public:
	Rational(int n = 0, int d = 1) : numer(n), denom(d) {
		/*
		 * a denominitor of 0 means infinity, which is most decidedly
		 * not rational...
		 */
		if (denom == 0)
			throw std::invalid_argument(
					"Rational numbers cannot have a denominator of zero.");
		reduce();
	}

	const std::string to_str() const;
	const int numerator() const { return numer; }
	const int denominator() const { return denom; }

private:
	int numer;
	int denom;

	void reduce();
};

/*
 * This function calculates the greatest common divisor of two integers
 * and returns it.
 */
inline int gcd(int x, int y) {
	if (y == 0)
		return x;
	else
		return gcd(y, x % y);
}

/*
 * This function calculates the lowest common multiple of two integers
 * and returns it.
 */
inline int lcm(int x, int y) {
	return (x * y) / gcd(x, y);
}

/*
 * This function returns a nice string representation of a rational number.
 */
inline const std::string Rational::to_str() const {
		std::stringstream sout;
		sout << numer;
		/* Only display the fraction part if it is required... */
		if (denom > 1) {
			sout << "/" << denom;
		}
		return sout.str();
	}

/*
 * This function will reduce our fraction, even eliminating the denominator
 * if it is not needed.  If both the numerator and denominator are negative, it
 * will flip the sign for us as well.
 */
inline void Rational::reduce() {
		int g = gcd(numer, denom);
		numer /= g;
		denom /= g;

		if (numer < 0 && denom < 0) {
			abs(numer);
			abs(denom);
		}
	}

/*
 * The reciprocal of a rational number A/B = B/A.
 */
inline const Rational reciprocal(const Rational& r) {
	return Rational(r.denominator(), r.numerator());
}

/*
 * This lets us feed Rationals into ostreams for IO
 */
inline std::ostream& operator<<(std::ostream& out, const Rational& r) {
	return out << r.to_str();
}

/*
 * The following functions implement arithmetic operators...
 */

inline const Rational operator+(const Rational& lhs, const Rational& rhs) {
	int l = lcm(lhs.denominator(), rhs.denominator());
	return Rational((lhs.numerator() * l / lhs.denominator()) + (rhs.numerator()
			* l / rhs.denominator()), l);
}

inline const Rational operator-(const Rational& lhs, const Rational& rhs) {
	int l = lcm(lhs.denominator(), rhs.denominator());
	return Rational((lhs.numerator() * l / lhs.denominator()) - (rhs.numerator()
			* l / rhs.denominator()), l);
}

inline const Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator()
			* rhs.denominator());
}

inline const Rational operator/(const Rational& lhs, const Rational& rhs) {
	return lhs * reciprocal(rhs);
}

}

#endif /* RATIONAL_H_ */
