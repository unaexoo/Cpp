#include "MixedFraction.h"

MixedFraction::MixedFraction(int _num, int _den, int _whole) : Fraction(_num, _den), whole(_whole) {
	cancel();
}
MixedFraction::MixedFraction(const MixedFraction& par) : Fraction(par.getNum(), par.getDen()), whole(par.whole) {}

int MixedFraction::getWhole() {
	whole = getNumer() / getDenom();
	return whole;
}
int MixedFraction::getNumer() {
	return Fraction::getNum();
}
int MixedFraction::getDenom() {
	return Fraction::getDen();
}

Fraction MixedFraction::getFrac() {
	int _num = getNumer();
	int _den = getDenom();

	if (_num % _den != 0) {
		_num = _num % _den;
	}
	return Fraction(_num,_den);
}
Fraction MixedFraction::toFrac() {
	// ºÐ¸ð : whole * den + num
	int _num = getNumer();
	int _den = getDenom();

	_num = whole * _den + _num;
	return Fraction(_num, _den);
}
void MixedFraction::show() {
	cout << whole << "*";
	Fraction::show();
}
MixedFraction& MixedFraction::add(const MixedFraction& rval) {
	int _num = rval.getNum();
	int _den = rval.getDen();
	Fraction val(_num, _den);
	Fraction res = Fraction::add(val);
	whole = rval.whole + whole;
	return *this;
}
MixedFraction& MixedFraction::sub(const MixedFraction& rval) {
	int _num = rval.getNum();
	int _den = rval.getDen();
	Fraction val(_num, _den);
	Fraction res = Fraction::sub(val);
	whole = rval.whole - whole;
	return *this;
}
MixedFraction& MixedFraction::mul(const MixedFraction& rval) {
	int _num = rval.getNum();
	int _den = rval.getDen();
	Fraction val(_num, _den);
	Fraction res = Fraction::mul(val);
	whole = rval.whole * whole;
	return *this;
}
MixedFraction& MixedFraction::div(const MixedFraction& rval) {
	int _num = rval.getNum();
	int _den = rval.getDen();
	Fraction val(_num, _den);
	Fraction res = Fraction::div(val);
	whole = rval.whole / whole;
	return *this;
}

MixedFraction MixedFraction::add(const MixedFraction& rval, const MixedFraction& lval) {
	MixedFraction res(rval);
	res.add(lval);
	return MixedFraction(res);
}
MixedFraction MixedFraction::sub(const MixedFraction& rval, const MixedFraction& lval) {
	MixedFraction res(rval);
	res.sub(lval);
	return MixedFraction(res);
}
MixedFraction MixedFraction::mul(const MixedFraction& rval, const MixedFraction& lval) {
	MixedFraction res(rval);
	res.mul(lval);
	return MixedFraction(res);
}
MixedFraction MixedFraction::div(const MixedFraction& rval, const MixedFraction& lval) {
	MixedFraction res(rval);
	res.div(lval);
	return MixedFraction(res);
}
void  MixedFraction::cancel() {
	int num = getNumer();
	int _den = getDenom();

	if (num / _den > 0) {
		num = num % _den;
		whole += num / _den;
	}
}
int  MixedFraction::euclidGcd(int lval, int rval) {
	return (rval == 0) ? lval : euclidGcd(rval, lval % rval);
}
int  MixedFraction::myLcm(int lval, int rval) {
	return lval * rval / euclidGcd(lval, rval);
}