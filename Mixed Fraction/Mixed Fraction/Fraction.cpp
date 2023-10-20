#include "Fraction.h"

Fraction::Fraction(int _num, int _den) :Rational(_num), den(_den) {}
Fraction::Fraction(const Fraction& par) : Rational(par.getNumer()),den(par.den) {}

int Fraction::getNum() const {
	return Rational::getNumer();
}
int Fraction::getDen() const {
	return Rational::getDenom();
}
void Fraction::incr() {
	Rational::add(den);
}
void Fraction::decr() {
	Rational::sub(den);
}

void Fraction::show() {
	cout << getNum() << "/" << den;
}
Fraction& Fraction::add(const Fraction& rval) {
	Rational::add(rval);
	return *this;
}
Fraction& Fraction::sub(const Fraction& rval) {
	Rational::sub(rval);
	return *this;
}
Fraction& Fraction::mul(const Fraction& rval) {
	Rational::mul(rval);
	return *this;
}
Fraction& Fraction::div(const Fraction& rval) {
	Rational::div(rval);
	return *this;
}
Fraction& Fraction::pow(const Rational& rval) {
	Rational::pow2(rval.getNumer());
	den ^= rval.getDenom();
	return *this;
}

Fraction Fraction::add(const Fraction& rval, const Fraction& lval) {
	Fraction res(rval);
	res.add(lval);
	return Fraction(res);
}
Fraction Fraction::sub(const Fraction& rval, const Fraction& lval) {
	Fraction res(rval);
	res.sub(lval);
	return Fraction(res);
}
Fraction Fraction::mul(const Fraction& rval, const Fraction& lval) {
	Fraction res(rval);
	res.mul(lval);
	return Fraction(res);
}
Fraction Fraction::div(const Fraction& rval, const Fraction& lval) {
	Fraction res(rval);
	res.div(lval);
	return Fraction(res);
}
Fraction Fraction::pow(const Fraction& rval, const Fraction& lval) {
	Fraction res(rval);
	res.pow(lval);
	return Fraction(res);
}
