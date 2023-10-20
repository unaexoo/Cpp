#include<iostream>
#include"Rational.h"
using namespace std;

Rational::Rational(int _num, int _den) : num(_num), den(_den) {
	cancel();
}

Rational::Rational(double real) {
	int cnt = 0, tmp = real;
	while (tmp * 10 != static_cast<int>(real * 10)) {
		tmp = real *= 10;
		cnt++;
	}
	num = real;
	den = pow(10, cnt);
	cancel();
}

Rational::Rational(const Rational& par) : num(par.num), den(par.den) {};
Rational::~Rational() {};

void Rational::show() {
	cout << num << "/" << den;
}

double Rational::eval() const {
	return static_cast<double>(num) / den;
}

int Rational::getNumer() const {
	return num;
}
int Rational::getDenom() const {
	return den;
}
int Rational::getWhole() const {
	return num / den;
}
double Rational::getFracPart() {
	return fracPart().eval();
}

Rational Rational::fracPart() {
	return Rational(num % den, den);
}
Rational Rational::reciprocal() {
	return Rational(den, num);
}

Rational& Rational::add(const Rational val) {
	int gcd = euclidGcd(den, val.den);
	int _den = myLcm(den, val.den);
	int _num = num * val.den / gcd + val.num * den / gcd;

	num = _num;
	den = _den;

	return *this;
}
Rational Rational::add(const Rational lval, const Rational rval) {
	int gcd = euclidGcd(lval.den, rval.den);
	int den = myLcm(lval.den, rval.den);
	int num = lval.num * rval.den / gcd + rval.num * lval.den / gcd;
	return Rational(num, den);
}

Rational& Rational::sub(const Rational val) {
	Rational minus(-val.num, val.den);
	return add(minus);
}

Rational Rational::sub(const Rational lval, const Rational rval) {
	Rational minus(-rval.num, rval.den);
	return Rational::add(lval, minus);
}

Rational& Rational::mul(const Rational val) {
	int _den = myLcm(den, val.den);
	int _num = num * val.num;
	int gcd = euclidGcd(den, num);

	num = _num;
	den = _den;

	return *this;
}
Rational Rational::mul(const Rational lval, const Rational rval) {
	int _den = myLcm(lval.den, rval.den);
	int _num = lval.num * rval.num;

	int gcd = euclidGcd(_den, _num);

	return Rational(_num / gcd, _den / gcd);
}

Rational& Rational::div(const Rational val) {
	Rational recip(val.den, val.num);
	return mul(recip);
}
Rational Rational::div(const Rational lval, const Rational rval) {
	return Rational::mul(lval, Rational(rval.den, rval.num));
}

Rational& Rational::pow2() {
	return mul(*this);
}
Rational Rational::pow2(const Rational val) {
	return Rational::mul(val, val);
}

void Rational::cancel() {
	int gcd = euclidGcd(den, num);
	den /= gcd;
	num /= gcd;
	if (den < 0) {
		den += -1;
		num *= -1;
	}
}
int Rational::euclidGcd(int lval, int rval) {
	return (rval == 0) ? lval : euclidGcd(rval, lval % rval);
}
int Rational::myLcm(int lval, int rval) {
	return lval * rval / euclidGcd(lval, rval);
}