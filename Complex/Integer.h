#ifndef INTEGER_H
#define INTEGER_H

#include <cassert>
#include <climits>
#include <algorithm>
#include <iostream>

class Integer {
public:
	Integer(int _val = 0);
	Integer(const Integer& par);

	int getVal() const;	
	int setVal(const int _val);

	int add(int amount);
	int remove(int amount);
	int incr();
	int decr();
	void show() const { std::cout << num; }
	friend std::ostream& operator<<(std::ostream& os, const Integer& rval);

public:
	operator int() const;
	Integer operator-();
	Integer& operator++();
	Integer operator++(int dummy);
	Integer& operator--();
	Integer operator--(int dummy);

public:
	Integer& add(const Integer& rval);
	Integer& sub(const Integer& rval);
	Integer& mul(const Integer& rval);
	Integer& div(const Integer& rval);
	Integer& mod(const Integer& rval);
	Integer& pow(const Integer& rval);
public:
	Integer& operator+=(const Integer& rval);
	Integer& operator-=(const Integer& rval);
	Integer& operator*=(const Integer& rval);
	Integer& operator/=(const Integer& rval);
	Integer& operator%=(const Integer& rval);
	Integer& operator^=(const Integer& rval);

public:
	bool equals(const Integer& rval) const;
	bool neq(const Integer& rval) const;
	bool less(const Integer& rval) const;
	bool leq(const Integer& rval) const;
	bool greater(const Integer& rval) const;
	bool geq(const Integer& rval) const;
public:
	bool operator==(const Integer& rval) const;
	bool operator!=(const Integer& rval) const;
	bool operator<(const Integer& rval) const;
	bool operator<=(const Integer& rval) const;
	bool operator>(const Integer& rval) const;
	bool operator>=(const Integer& rval) const;

public:
	static Integer add(const Integer& lval, const Integer& rval);
	static Integer sub(const Integer& lval, const Integer& rval);
	static Integer mul(const Integer& lval, const Integer& rval);
	static Integer div(const Integer& lval, const Integer& rval);
	static Integer mod(const Integer& lval, const Integer& rval);
	static Integer pow(const Integer& lval, const Integer& rval);
public:
	friend Integer operator+(const Integer& lval, const Integer& rval);
	friend Integer operator-(const Integer& lval, const Integer& rval);
	friend Integer operator*(const Integer& lval, const Integer& rval);
	friend Integer operator/(const Integer& lval, const Integer& rval);
	friend Integer operator%(const Integer& lval, const Integer& rval);

private:
	void close();
		
public:
	static const int MAX_VAL;
	static const int MIN_VAL;

private:
	int num;
};

#endif // INTEGER_H