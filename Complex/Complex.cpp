#include "Complex.h" 

using namespace std;

Complex::Complex(const Frac& _real, const Frac& _img) : real(_real), img(_img) {}
Complex::Complex(const Complex& par) : real(par.real), img(par.img) {}

Frac Complex::getRe() const { 
	return real; 
}
Frac Complex::getIm() const { 
	return img;
}
Frac Complex::getAbs() const {
	//Frac abs = Frac::add(std::pow(real.getVal(), 2), std::pow(img.getVal(), 2));
	Frac abs = std::pow(real.getVal(), 2) + std::pow(img.getVal(), 2);
	double temp = sqrt(abs.getVal());

	return Frac(temp);
}
Frac Complex::getArg() const {
	double a, b;
	a = real.getVal();
	b = img.getVal();
	double theta = atan2(b, a);

	return Frac(theta);
}
Complex Complex::getConj() const {
	Frac _img(-img.getVal());
	return Complex(real, _img);
}

Complex& Complex::add(const Complex& rval){
	real += rval.real;
	img += rval.img;
	return *this;
}
Complex& Complex::sub(const Complex& rval) {
	real -= rval.real;
	img -= rval.img;
	return *this;
}
Complex& Complex::mul(const Complex& rval) {
	//Frac _real = Frac::sub(Frac::mul(real, rval.real), Frac::mul(img,  rval.img)); // 실수부(ac - bd)
	//Frac _img  = Frac::add(Frac::mul(img,  rval.real), Frac::mul(real, rval.img)); // 허수부(bc + ad)
	Frac _real = (real * rval.real) - (img * rval.img);
	Frac _img = (img * rval.real) + (real * rval.img);
	real = _real;
	img  = _img;

	return *this;
}
Complex& Complex::div(const Complex& rval) {	
	Frac _den = rval * (rval.getConj()).getRe();
	Frac _real = (real * rval.real) + (img + rval.img);
	Frac _img = (img * rval.real) - (real * rval.img);

	real = Frac::div(_real, _den);
	img  = Frac::div(_img,  _den);

	return *this;
}

Complex Complex::add(const Complex& lval, const Complex& rval){
	Complex res(lval);
	//res.add(rval);
	res += rval;
	return Complex(res);
}
Complex Complex::sub(const Complex& lval, const Complex& rval){
	Complex res(lval);
	res -= rval;
	return Complex(res);
}
Complex Complex::mul(const Complex& lval, const Complex& rval){
	Complex res(lval);
	res *= rval;
	return Complex(res);
}
Complex Complex::div(const Complex& lval, const Complex& rval){
	Complex res(lval);
	res /= rval;
	return Complex(res);
}

bool Complex::equals(const Complex& rval) const {
	return real == rval.real && img == rval.img;
}
bool Complex::neq(const Complex& rval) const {
	return !equals(rval);
}

void Complex::show() const {
	cout << "(";
	real.show();
	cout << ") + (";
	img.show();
	cout << ")i ";
}
Complex::operator double() const {
	return getAbs();
}
Complex& Complex::operator++() {
	real.incr();
	return *this;
}
Complex Complex::operator++(int dummy) {
	int temp = getRe();
	real += 1;
	int _img = img;
	return Complex(temp, _img);
}
Complex& Complex::operator--() {
	real.decr();
	return *this;
}
Complex Complex::operator--(int dummy) {
	int temp = getRe();
	real -= 1;
	int _img = img;
	return Complex(temp, _img);
}
Complex Complex::operator-() {
	return Complex(getConj().real, getConj().img);
}

Complex& Complex::operator+=(const Complex& rval) {
	return add(rval);
}
Complex& Complex::operator-=(const Complex& rval) {
	return sub(rval);
}
Complex& Complex::operator*=(const Complex& rval) {
	return mul(rval);
}
Complex& Complex::operator/=(const Complex& rval) {
	return div(rval);
}

// friend
Complex operator+(const Complex& lval, const Complex& rval) {
	return Complex::add(lval, rval);
}
Complex operator-(const Complex& lval, const Complex& rval) {
	return Complex::sub(lval, rval);
}
Complex operator*(const Complex& lval, const Complex& rval) {
	return Complex::mul(lval, rval);
}
Complex operator/(const Complex& lval, const Complex& rval) {
	return Complex::div(lval, rval);
}
bool Complex::operator==(const Complex& rval) const {
	return equals(rval);
}
bool Complex::operator!=(const Complex& rval) const {
	return neq(rval);
}
std::ostream& operator<<(std::ostream& os, const Complex& rval) {
	os << "(" << rval.real << ") + (" << rval.img << ")i ";
	return os;
}