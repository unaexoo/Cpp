#ifndef FRACATION_H
#define FRACATION_H
#include "Rational.h"
class Fraction:public Rational
{
public:
	Fraction(int _num=0, int _den = 1);
	Fraction(const Fraction& par);

	int getNum() const;
	int getDen() const;

	void incr();
	void decr();
	void show();

public:
	Fraction& add(const Fraction& rval);
	Fraction& sub(const Fraction& rval);
	Fraction& mul(const Fraction& rval);
	Fraction& div(const Fraction& rval);
	Fraction& pow(const Rational& rval);

	static Fraction add(const Fraction& rval, const Fraction& lval);
	static Fraction sub(const Fraction& rval, const Fraction& lval);
	static Fraction mul(const Fraction& rval, const Fraction& lval);
	static Fraction div(const Fraction& rval, const Fraction& lval);
	static Fraction pow(const Fraction& rval, const Fraction& lval);

private:
	int den;
};

#endif