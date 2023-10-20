#ifndef FRAC_H
#define FRAC_H

#include "Integer.h"
class Frac : public Integer {
public:	
	Frac(int _num = 0, int _den = 1);
	Frac(const Frac& par);
	Frac(double _dval);

	void setNum(int _num);
	int getNum() const;
	void setDen(int _den);
	int getDen() const;
	double getVal() const;
	void setVal(int _num = 0, int _den = 1);
	void setVal(double dval);

	void incr();
	void decr();
	void show() const;
	friend std::ostream& operator<<(std::ostream& os, const Frac& rval);

public:
	operator int() const;
	operator double() const;
	Frac operator-();
	Frac& operator++();
	Frac operator++(int dummy);
	Frac& operator--();
	Frac operator--(int dummy);
public:
	Frac& add(const Frac& rval);
	Frac& sub(const Frac& rval);
	Frac& mul(const Frac& rval);
	Frac& div(const Frac& rval);
//	Frac& mod(const Frac& rval);
	Frac& pow(const Integer& rval);
public:
	Frac& operator+=(const Frac& rval);
	Frac& operator-=(const Frac& rval);
	Frac& operator*=(const Frac& rval);
	Frac& operator/=(const Frac& rval);
	Frac& operator^=(const Frac& rval);
public:

	static Frac add(const Frac& lval, const Frac& rval);
	static Frac sub(const Frac& lval, const Frac& rval);
	static Frac mul(const Frac& lval, const Frac& rval);
	static Frac div(const Frac& lval, const Frac& rval);
	static Frac pow(const Frac& lval, const Frac& rval);
public:
	bool equals(const Frac& rval) const;
	bool neq(const Frac& rval) const;
	bool less(const Frac& rval) const;
	bool leq(const Frac& rval) const;
	bool greater(const Frac& rval) const;
	bool geq(const Frac& rval) const;
public:
	bool operator==(const Frac& rval) const;
	bool operator!=(const Frac& rval) const;
	bool operator<(const Frac& rval) const;
	bool operator<=(const Frac& rval) const;
	bool operator>(const Frac& rval) const;
	bool operator>=(const Frac& rval) const;
public:
	friend Frac operator+(const Frac& lval, const Frac& rval);
	friend Frac operator-(const Frac& lval, const Frac& rval);
	friend Frac operator*(const Frac& lval, const Frac& rval);
	friend Frac operator/(const Frac& lval, const Frac& rval);
private:
	void cancel();
	int euclidGcd(int a, int b) const;
	int myGcd(int a, int b) const;
	int myLcm(int a, int b) const;

private:
	int den;
};

#endif