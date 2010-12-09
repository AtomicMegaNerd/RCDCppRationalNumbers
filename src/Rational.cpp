#include "Rational.h"

namespace rcd {

const std::string Rational::to_str() const {
	std::stringstream sout;
	sout << numer;
	/* Only display the fraction part if it is required... */
	if (denom > 1) {
		sout << "/" << denom;
	}
	return sout.str();
}

void Rational::reduce() {
	int g = gcd(numer, denom);
	numer /= g;
	denom /= g;

	if (numer < 0 && denom < 0) {
		abs(numer);
		abs(denom);
	}
}

const Rational reciprocal(const Rational& r) {
	return Rational(r.denominator(), r.numerator());
}

std::ostream& operator<<(std::ostream& out, const Rational& r) {
	return out << r.to_str();
}

const Rational operator+(const Rational& lhs, const Rational& rhs) {
	int l = lcm(lhs.denominator(), rhs.denominator());
	return Rational((lhs.numerator() * l / lhs.denominator())
			+ (rhs.numerator() * l / rhs.denominator()), l);
}

const Rational operator-(const Rational& lhs, const Rational& rhs) {
	int l = lcm(lhs.denominator(), rhs.denominator());
	return Rational((lhs.numerator() * l / lhs.denominator())
			- (rhs.numerator() * l / rhs.denominator()), l);
}

const Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator()
			* rhs.denominator());
}

const Rational operator/(const Rational& lhs, const Rational& rhs) {
	return lhs * reciprocal(rhs);
}

}
