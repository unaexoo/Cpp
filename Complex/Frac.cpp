#include "Frac.h"

Frac::Frac(int _num, int _den) : Integer(_num), den(_den) { cancel(); }
Frac::Frac(const Frac& par) : Integer(par.getNum()), den(par.den) { cancel(); }
Frac::Frac(double _dval) { 
	setVal(_dval); 
}

void Frac::setNum(int _num) { 
	Integer::setVal(_num); 
}
int Frac::getNum() const { 
	return Integer::getVal(); 
}
void Frac::setDen(int _den) { 
	den = _den; 
}
int Frac::getDen() const { 
	return den; 
}
double Frac::getVal() const {
	return static_cast<double>(Integer::getVal()) / den;
}
void Frac::setVal(int _num, int _den) {
	Integer::setVal(_num);
	den = _den;
}
void Frac::setVal(double dval) {
	int count = 0, temp = static_cast<int>(dval);
	while (temp * 10 != static_cast<int>(dval * 10)) { // double은 == 불가
	//	std::cout << "temp:" << temp << ", temp * 10: " << static_cast<int>(dval * 10) << std::endl;
		int ovf_chk = static_cast<int>(dval * 10);
		if (dval * ovf_chk < 0 || ovf_chk == std::numeric_limits<int>::min()) {	// 정수 오버플로우 검사
			break;
		}
		temp = static_cast<int>(dval *= 10);
		count++;
	}
	Integer::setVal(static_cast<int>(dval));
	den = static_cast<int>(std::pow(10, count));		// ^는 상황에 따라서 XOR
	cancel();
}

void Frac::incr() {
	Integer::add(den);
}
void Frac::decr() {
	Integer::sub(den);
}
void Frac::show() const {
	Integer::show();
	std::cout << " / " << den;
}
std::ostream& operator<<(std::ostream& os, const Frac& rval) {
	os << static_cast<Integer>(rval);
	os << " / " << rval.den;
	return os;
}
Frac& Frac::add(const Frac& rval) {
	int gcd = myGcd(den, rval.den);

	int _den = myLcm(den, rval.den);
	int _num = Integer::getVal() * rval.den / gcd + rval.getNum() * den / gcd;

	Integer::setVal(_num);
	den = _den;
	return *this;
}
Frac& Frac::sub(const Frac& rval) {
	Frac minus(-rval.getNum(), rval.den);
	return add(minus);
}
Frac& Frac::mul(const Frac& rval) {	
	int _num = Integer::getVal() * rval.getNum();
	int _den = den * rval.den;
		
	int gcd = myGcd(_den, _num);

	Integer::setVal(_num / gcd);
	den = _den / gcd;
	return *this;
}
Frac& Frac::div(const Frac& rval) {
	Frac recip(rval.den, rval.getNum());
	return mul(recip);
}

Frac& Frac::pow(const Integer& rval) {
	Integer::pow(rval.getVal());							// 분자 거듭제곱
	den = static_cast<int>(std::pow(den, rval.getVal()));	// 분모 거듭제곱
	return *this;
}

Frac Frac::add(const Frac& lval, const Frac& rval) {
	Frac res(lval);
	return Frac(res.add(rval));
}
Frac Frac::sub(const Frac& lval, const Frac& rval) {
	Frac res(lval);
	return Frac(res.sub(rval));
}
Frac Frac::mul(const Frac& lval, const Frac& rval) {
	Frac res(lval);
	return Frac(res.mul(rval));
}
Frac Frac::div(const Frac& lval, const Frac& rval) {
	Frac res(lval);
	return Frac(res.div(rval));
}
Frac Frac::pow(const Frac& lval, const Frac& rval) {
	Frac res(lval);
	return Frac(res.pow(rval));
}

bool Frac::equals(const Frac& rval) const {
	return getNum() == rval.getNum() && den == rval.den;
}
bool Frac::neq(const Frac& rval) const {
	// 1. 독자적 구현, 2. 위임 (재사용), 3. 호출 (재사용)
	// return getNum() != rval.getNum() || den != rval.den;
	return !equals(rval);
}
bool Frac::less(const Frac& rval) const {
	return this->getVal() < rval.getVal();
	// return !geq(rval);
}
bool Frac::leq(const Frac& rval) const {
	return less(rval) || equals(rval);
	// return !greater(rval);
}
bool Frac::greater(const Frac& rval) const {
	return this->getVal() > rval.getVal();
	// return !leq(rval);
}
bool Frac::geq(const Frac& rval) const {
	return greater(rval) || equals(rval);
	// return !less(rval);
}

void Frac::cancel() {
	int gcd = myGcd(Integer::getVal(), den);
	// Integer::setVal(Integer::getVal() / gcd);
	Integer::div(gcd);
	den /= gcd;

	if (den < 0) {
		den *= -1;
		Integer::mul(-1);
	}
}
int Frac::euclidGcd(int a, int b) const {
	if (b == 0) return a;

	return euclidGcd(b, a % b);
}
int Frac::myGcd(int a, int b) const {
	int bigger = std::max(a, b);
	int smaller = std::min(a, b);
	return euclidGcd(bigger, smaller);
}
int Frac::myLcm(int a, int b) const {
	return a * b / euclidGcd(a, b); 
}
// 단항 연산
Frac::operator int() const {
	return getNum() / getDen();
}
Frac::operator double() const {
	return getVal();
}
Frac Frac::operator-() {
	return Frac(-getVal());
}
Frac& Frac::operator++() {
	incr();
	return *this;
}
Frac Frac::operator++(int dummy) {
	int temp = getVal();
	incr();
	return Frac(temp);
}
Frac& Frac::operator--() {
	decr();
	return *this;
}
Frac Frac::operator--(int dummy) {
	int temp = getVal();
	decr();
	return Frac(temp);
}
// 이항 연산
Frac& Frac::operator+=(const Frac& rval) {
	return add(rval);
}
Frac& Frac::operator-=(const Frac& rval) {
	return sub(rval);
}
Frac& Frac::operator*=(const Frac& rval) {
	return mul(rval);
}
Frac& Frac::operator/=(const Frac& rval) {
	return div(rval);
}
Frac& Frac::operator^=(const Frac& rval) {
	return pow(rval);
}
// 이항연산 프렌드
Frac operator+(const Frac& lval, const Frac& rval) {
	return Frac::add(lval, rval);
}
Frac operator-(const Frac& lval, const Frac& rval) {
	return Frac::sub(lval, rval);
}
Frac operator*(const Frac& lval, const Frac& rval) {
	return Frac::mul(lval, rval);
}
Frac operator/(const Frac& lval, const Frac& rval) {
	return Frac::div(lval, rval);
}

bool Frac::operator==(const Frac& rval) const {
	return equals(rval);
}
bool Frac::operator!=(const Frac& rval) const {
	return neq(rval);
}
bool Frac::operator<(const Frac& rval) const {
	return less(rval);
}
bool Frac::operator<=(const Frac& rval) const {
	return leq(rval);
}
bool Frac::operator>(const Frac& rval) const {
	return greater(rval);
}
bool Frac::operator>=(const Frac& rval) const {
	return geq(rval);
}
