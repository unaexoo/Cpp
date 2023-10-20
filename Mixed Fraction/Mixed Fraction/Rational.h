#ifndef RATIONAL_H
#define RATIONAL_H
#include<iostream>
using namespace std;

// 유리수
class Rational
{
public:
	Rational(int _num, int _den);
	Rational(double real);
	Rational(const Rational& par);
	~Rational();

	void show();

	double eval() const; // 소수
	int getNumer() const;	// 분자 반환
	int getDenom() const;	// 분모 반환
	int getWhole() const;	// 자연수 반환
	double getFracPart();	//소수부만 반환


	Rational fracPart();
	Rational reciprocal();
public:
	Rational& add(const Rational val);
	static Rational add(const Rational lval, const Rational rval);

	Rational& sub(const Rational val);
	static Rational sub(const Rational lval, const Rational rval);

	Rational& mul(const Rational val);
	static Rational mul(const Rational lval, const Rational rval);

	Rational& div(const Rational val);
	static Rational div(const Rational lval, const Rational rval);

	Rational& pow2();
	static Rational pow2(const Rational val);
private:
	void cancel();
	static int euclidGcd(int lval, int rval);
	static int myLcm(int lval, int rval);
private:
	int num;	// 분자
	int den;	// 분모
};

#endif // !RATIONAL_H