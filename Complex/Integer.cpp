#include "Integer.h"

const int Integer::MAX_VAL = INT_MAX;
const int Integer::MIN_VAL = INT_MIN;

Integer::Integer(int _num) : num(_num) { close(); }
Integer::Integer(const Integer& par) : num(par.num) { close(); }

int Integer::getVal() const { return num; }
int Integer::setVal(const int _num) {
	num = _num;
	close();
	return num;
}
int Integer::add(int amount) {
	num += amount;
	close();
	return num;
}
int Integer::remove(int amount) {
	return add(-amount);
}
int Integer::incr() {
	return add(1);
}
int Integer::decr() {
	return remove(1);
}

Integer::operator int() const {
	return getVal();
}
Integer Integer::operator-() {
	return Integer(-num);
}

Integer& Integer::operator++() {
	incr();
	return *this;
}
Integer Integer::operator++(int dummy) {
	int temp = num;
	incr();
	return Integer(temp);
}
Integer& Integer::operator--() {
	decr();
	return *this;
}
Integer Integer::operator--(int dummy) {
	int temp = num;
	decr();
	return Integer(temp);
}

Integer& Integer::add(const Integer& rval) {
	num += rval.num;
	return *this;
}
Integer& Integer::sub(const Integer& rval) {
	num -= rval.num;
	return *this;
}
Integer& Integer::mul(const Integer& rval) {
	num *= rval.num;
	return *this;
}
Integer& Integer::div(const Integer& rval) {
	assert(rval.num != 0);
	num /= rval.num;
	return *this;
}
Integer& Integer::mod(const Integer& rval) {
	assert(rval.num != 0);
	num %= rval.num;
	return *this;
}
Integer& Integer::pow(const Integer& rval) {
	num = static_cast<int>(std::pow(num, rval.num));
	return *this;
}
Integer& Integer::operator+=(const Integer& rval) {
	return add(rval);
}
Integer& Integer::operator-=(const Integer& rval) {
	return sub(rval);
}
Integer& Integer::operator*=(const Integer& rval) {
	return mul(rval);
}
Integer& Integer::operator/=(const Integer& rval) {
	return div(rval);
}
Integer& Integer::operator%=(const Integer& rval) {
	return mod(rval);
}
Integer& Integer::operator^=(const Integer& rval) {
	return pow(rval);
}

bool Integer::equals(const Integer& rval) const {
	return num == rval.num;
}
bool Integer::neq(const Integer& rval) const {
	// return val != rval.val;		// 별도 구현
	return !equals(rval);			// 함수 재사용
}
bool Integer::less(const Integer& rval) const {
	return num < rval.num;
}
bool Integer::leq(const Integer& rval) const {
	// return val < rval.val || val == rval.val;	// 별도 구현
	return less(rval) || equals(rval);				// 함수 재사용
}
bool Integer::greater(const Integer& rval) const {
	return num > rval.num;
}
bool Integer::geq(const Integer& rval) const {
	// return val > rval.val || val == rval.val;	// 별도 구현
	return greater(rval) || equals(rval);			// 함수 재사용
}
bool Integer::operator==(const Integer& rval) const {
	return equals(rval);
}
bool Integer::operator!=(const Integer& rval) const {
	return neq(rval);
}
bool Integer::operator<(const Integer& rval) const {
	return less(rval);
}
bool Integer::operator<=(const Integer& rval) const {
	return leq(rval);
}
bool Integer::operator>(const Integer& rval) const {
	return greater(rval);
}
bool Integer::operator>=(const Integer& rval) const {
	return geq(rval);
}

Integer Integer::add(const Integer& lval, const Integer& rval) {
	return Integer(lval.num + rval.num);
}
Integer Integer::sub(const Integer& lval, const Integer& rval) {
	return Integer(lval.num - rval.num);
}
Integer Integer::mul(const Integer& lval, const Integer& rval) {
	return Integer(lval.num * rval.num);
}
Integer Integer::div(const Integer& lval, const Integer& rval) {
	assert(rval.num != 0);
	return Integer(lval.num / rval.num);
}
Integer Integer::mod(const Integer& lval, const Integer& rval) {
	assert(rval.num != 0);
	return Integer(lval.num % rval.num);
}
Integer Integer::pow(const Integer& lval, const Integer& rval) {
	return Integer(lval.num ^ rval.num);
}
Integer operator+(const Integer& lval, const Integer& rval) {
	return Integer::add(lval, rval);
}
Integer operator-(const Integer& lval, const Integer& rval) {
	return Integer::sub(lval, rval);
}
Integer operator*(const Integer& lval, const Integer& rval) {
	return Integer::mul(lval, rval);
}
Integer operator/(const Integer& lval, const Integer& rval) {
	return Integer::div(lval, rval);
}
Integer operator%(const Integer& lval, const Integer& rval) {
	return Integer::mod(lval, rval);
}

std::ostream& operator<<(std::ostream& os, const Integer& rval) {
	os << rval.num;
	return os;
}

void Integer::close() {
	num = std::max(MIN_VAL, num);
	num = std::min(num, MAX_VAL);
}