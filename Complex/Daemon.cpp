//문제 해결 원리 : 먼저 해당 문제는 연산 오버로드를 구현하는 것이다.연산자 오버로드가 완료된 Integer클래스와 연산자 오버로드가 되지 않은 Frac과 Complax클래스가 주어진다.
//				Fraction과 Complax를 연산자 오버로드를 수행할 부분들을 추가해준다.단항 연산자와 이항 연산자를 정의해주고 operator의 경우 const함수로 정의해주고, 
//				자료형& 의 경우 const 변수를 이용해서 정의해준다. 먼저 함수에 이미 정의되어 있는 기능들을 오버로드로 구현할 함수와 비교해준다.같은 기능을 수행하는
//				함수가 있다면 그 함수를 호출하여 오버로드 함수를 작성해준다. 연산자 오버로드의 가장 큰 장점은 코드 가독성을 높여주기에 코드를 이해하기 편해진다. 이를 활용하여 직관적인 코드 작성을 해볼 수 있다.
// 
//연산자 오버로드
//- 같은 연사자로 다른 처리를 하는 함수를 정의하는 것
//- 어떤 연산자를 사용해서 어떤 처리를 할 수 있게 해주는 문법
//
// # Complex.cpp에 정의되어 있던 사칙연산 함수들(semi, 완전)을 Frac으로 구현한 연산자 오버로딩을 통해 수정하였다. 또한, 크기를 구하는 getAbs()함수에도 오버로딩을 활용하여 수정하였다.
//	[1] Frac Complex::getAbs() const {...}
//		- Frac abs = std::pow(real.getVal(), 2) + std::pow(img.getVal(), 2);로 Frac에 정의된 + 를 이용하여 연산을 간결하게 표현하게 해주었다. 

//	[1] Complex& Complex::add(const Complex& rval){...}
//		- real.add(rval.real), img.add(rval.img)를 Frac에 정의된 +=을 이용하여 수정하였다. -> real+=rval.real, img+=rval.img
//		- 이렇게 수정을 한 후 객체 누적이 이루어지 때문에 이전 연산 결과 출력과 차이는 없다.
//
//	[2] Complex& Complex::sub(const Complex& rval) {...}
//		- 위와 동일하게 Frac에 정의된 -=을 이용하여 수정하였기에 객체 누적과 연산 결과 출력은 이전과 동일하다.
// 
//	[3] Complex& Complex::mul(const Complex& rval) {...}
//		- 실수부(ac-bd), 허수부(bc+ad)를 연산자 오버로딩을 이용하여 (real * rval.real) - (img * rval.img) 형식으로 정의하였다. 
//		  앞의 내용은 실수부의 구현이고 허수부의 구현도 동일한 방식으로 진행하였다.
// 
//	[4] Complex& Complex::div(const Complex& rval) {...}
//		- div의 경우 복소수의 실수화를 해주어야 한다. Frac에 정의된 * 를 이용하여 _den = rval * (rval.getConj()).getRe()으로 정의해주었다.
//		- _real과 _den은 위 mul의 연산과정과 동일하다.
//
//   +) 완전 부분도 semi와 비슷하다. 다만 마지막 새로운 객체를 반환하는 것에만 차이가 있다. 완전으로 구현된 add,sub, mul, div 대부분 Complex res(lval)에 해당 연산에 맞는 +=,-=,*=,/=를 이용해 res객체에 누적 후
//		새로운 객체로 반환해주었다.
//	
//}
// # Frac과 Complex의 연산자 오버로딩을 통한 구현 중 유사한 부분이 있어 유사한 부분을 묶어서 설명한다.
//	 1)operator int  or operator double : 각각 정수값과 실수값을 반환한다.
//   [1] Frac에서의 operator int는 Frac에서의 클래스에 정의되어 있는데 함수의 정수값이라고 하면 대분수 형식의 정수 부분이기에 getNum()과 getDen()함수를 호출하여 나누어 주었다.
//		opertator double의 경우 정수부를 제외한 실수부를 반환해주기 위해 이미 정의되어 있는 getVal()함수를 호출하여 정의해준다.
//
//	 [2] Compelx에서의 opertor double은 크기를 반환해주어야 해서 미리 정의되어 있는 getAbs() 함수를 호출해주었다.
//
//	2) 전위 연산자
//		# 전위 증가, 전위 감소 연산자(++k, --k)
//		- 호스트 객체를 먼저 한 단계 증감 시키고 증감된 객체를 반환하는데 단항 연산자이기에 매개변수 객체는 가지지 않고 호스트 객체 자체를 반환한다.
//
//	[1] Frac에서는 미리 정의되어 있는 incr()와 decr() 함수를 호출하여 증감을 시킨다.그리고 * this를 이용해서 반환한다.
//
//	[2] Complex에서는 정수부분만 증감을 시키기 위해 real.incr() 와 real.decr()를 호출한 후 * this를 통해 반환해주었다.
//
//
//	3) 후위 연산자
//	# 후위 증가, 후위 감소 연산자(k++, k--)
//		- 호스트 객체를 한 단계 증감 시키고 증감되지 않은 객체를 반환하는 연산자이다.
//		- 후위 증감 연산자는 값의 변경 전에 값을 반환한다.
//		- 임시로 temp를 선언한 후 값을 복사하고 호스트 객체를 변경 후 temp를 반환한다.
//		- 매개변수 int는 전위연산자와 후위연산자 구분을 위한 용도이기에 내부적 사용은 하지 않는다.
//		- 반환 객체는 부가 작용이 일어나기 전에 만들어진 객체이다.
//		- 부가 작용은 두 연산자는 호스트 객체를 변경
//
//	[1] Frac::operator++(int dummy) 그리고 Frac::operator--(int dummy) : temp를 선언 후 getVal()값을 저장하고 
//		incr() / decr() 시킨 후 temp를 새로운 객체의 값으로 반환 이때 반환되는 값은 증감되기 이전의 값이다.
//
//	[2] Complex::operator++(int dummy) 그리고 Complex::operator--(int dummy) : temp를 선언한 후 getRe()를 호출하여 실수부만 증감해준다.
//		그리고 temp를 새로운 객체의 값으로 반환한다.이후 1을 더하거나 빼서 다음 값이 변경되도록 한다.
//
//	4) - 연산자
//		- 부호 반전
//		- 단항 연산자는 호스트 객체가 피연산자이기에 매개변수 객체가 추가로 필요하지 않다.
//
//	[1] Frac::operator() - : getVal()를 호출하고 - 를 붙여 부호가 반전이 되게 한다.getval = num / den;
//	[2] Complex::operator() - : 복소수의 부호반전은 켤레복소수로 getConj()함수를 호출하여 real과 img를 Complex의 객체로 반환해준다.
//
//
//	5) 이항 연산자
//		- 2개 매개변수를 가지는 연산자
//		- 왼쪽 피연산자를 호스트 객체로, 오른쪽 피연산자를 매개변수 객체로 사용한다.
//		- const 한정자를 사용하여 매개변수가 변경이 일어나지 않게 해준다.호스트 객체는 수정이 일어나야 하므로 const 한정자를 붙일 수 없다.
//
//	[1] Frac::operator+=, Frac::operator-=, Frac::operator*=, Frac::operator/=, Frac::operator^=
//		- 해당 연산자들은 Frac에 이미 정의되어 있는 각각의 기능을 수행하는 add(), sub, mul, div, pow 함수를 호출하여 그 값을 호스트 객체에 누적하였다.
//
//	[2] Complex::operator+=, Complex::operator-=, Complex::operator*=, Complex::operator/=
//		- 해당 연산자들은 Complex 이미 정의되어 있는 각각의 기능을 수행하는 add(), sub, mul, div 함수를 호출하여 그 값을 호스트 객체에 누적하였다.
//
//	6) 프렌드를 이용한 이항 연산자 + , -, *, /
//		-한정자 friend : 호스트 객체를 기반으로 호출하는 멤버 함수는 아니지만, 클래스의 private 멤버에 접근할 수 있다.
//		- friend함수에는 호스트 객체가 없고 private 부여 받은 클래스의 멤버에 접근할 수 있다.또한, public getter / setter를 이용하지 않아도 된다.
//		- friend함수는 특정 클래스에 소속된 멤버 함수는 아니다.
//		- 클래스 내부에 선언하더라도 외부의 정의에서 출처 연산자::를 사용하지 않아야 한다.
//
//	[1] Frac operator+(const Frac & lval, const Frac & rval), Frac operator-, Frac operator*, Frac operator/ 
//		: Frac에 이미 선언되어 있는 add(), sub, mul, div 함수를 호출하고 그 값을 새로운 객체로 반환해주었다.
//		  friend의 특징으로 외부 정의에 출처 연산자를 사용하지 않아도 된다.
//
//	[2] Complex operator+(const Frac& lval, const Frac& rval), Complex operator-, Complex operator*, Complex operator/ 
//		: Complex 이미 선언되어 있는 add(), sub, mul, div 함수를 호출하고 그 값을 새로운 객체로 반환해주었다.
//
//	7) 동치, 부동, 관계
//	[1] Frac : Frac::operator==, Frac::operator!=, Frac::operator<, Frac::operator<=, Frac::operator>, Frac::operator>=
//	   : Frac의 클래스에 이미 정의되어 있는 함수를 이용하여 객체를 호스트에 누적하여 반환해준다.
//
//	[2] Complex::operator==, Complex::operator!= : Complex의 클래스에 이미 정의되어 있는 함수 이용
//
//	8) friend ostream &
//		-std::cout도 ostream 타입의 객체이다.
//		- ostream 내 여러 자료형이 << 연산자 오버로딩이 구현되어 있다.
//		- ostream 타입의 객체가 출력 연산자를 만나면 출력연산자 우측에 있는 것을 인수로 하는 ostream 클래스의 멤버 출력 연산자 오버로딩을 호출한다. << 연산자의 우측에 있는 데이터를 출력한다.
//
//	[1] Frac의 경우 os에 누적하면서 rval의 값을 저장하고 "/" 를 저장한 후 rval.den을 저장한 후 누적된 결과를 os를 통해서 반환 후 출력한다.
//		따라서 num / den인 분수 형태가 출력된다.
//
//	[2]  complex의 경우 os에 "("를 누적 후 실수값과 ") + ("를 저장하고 허수부(img), 그리고 ")i"를 os에 누적시켜준다.
//		그리고 os를 반환해준다.출력은(real) + (img)i로 나타난다.

#include "Frac.h"
#include "Complex.h"
#include <iostream>

using namespace std;

int main() {
	Frac f1(2, -7);
	cout << "f1 = " << f1 << endl;

	cout << "f1 + 1 = " << ++f1 << endl;
	cout << "f1 - 1 - 1 = " << ----f1 << endl;
	
	f1 = { 11, 3 } ;
	cout << "f1 = 11 / 3 = " << f1 << endl;
	cout << "f1 = " << static_cast<double>(f1) << endl;
	cout << endl;

	Frac f2(-3.1415);
	cout << "f2 = " << f2 << endl << endl;

	Frac f3(1, 2), f4(2, 3);
	cout << "f3 = " << f3 << endl;
	cout << "f4 = " << f4 << endl;

	Frac f5 = f3 + f4;
	cout << "f5 = f3 + f4 = " << f5 << endl;
	cout << "f3 += f4 = " << (f3 += f4) << endl;

	Frac f6 = f4 * f5;
	cout << "f6 = f4 * f5 = " << f4 << " * " << f5 << " = " << f6 << endl;
	cout << "f4 *= f5 = " << (f4 *= f5) << endl;

	Frac f7 = f6 / f1;
	cout << "f7 = f6 / f1 = " << f7 << endl;
	Frac f8 = Frac::pow(f7, 3);
	cout << "f8 = f7 ^ 3 = " << f8 << endl;

	cout << "f2 ^= 2 = " << (f2.pow(2)) << endl;

	///////////////////////////////////////////////////////////////////////////

	Complex c1(1.2, 2.89);
	Complex c2(3.14, 4.13);
	cout << "c1 = 1.2 + 2.89i = " << c1 << endl;
	cout << "c2 = 3.14 + 4.13i = " << c2 << endl;

	Complex c3 = c1 + c2;
	cout << "c3 = c1 + c2 = " << c3 << endl;
	
	Complex c4 = c1 - c2;
	cout << "c4 = c1 - c2 = " << c4 << endl;

	Complex c5 = c1 * c2;
	cout << "c5 = c1 * c2 = " << c5 << endl;

	Complex c6 = c1 / c2;
	cout << "c6 = c1 / c2 = " << c6 << endl << endl;

	cout << "Re(c6) = " << c6.getRe() << endl;
	cout << "Im(c6) = " << c6.getIm() << endl;
	
	cout << "arg(c6) = " << c6.getArg() << endl << endl;
		
	Complex c7(3, -4), c8(-1, 3);
	cout << "c7* = (3 - 4i)* = " << c7.getConj() << endl;
	cout << "c8* = (-1 + 3i)* = " << c8.getConj() << endl << endl;

	cout << "c7 * c7* = (3 - 4i) * (3 - 4i)* = " << (c7 * c7.getConj()) << endl;
	cout << "|c7| = |3 - 4i| = " << static_cast<Frac>(c7.getAbs()) << endl << endl;

	cout << "c8 * c8* = (-1 + 3i) * (-1 + 4i)* = " << (c8 * c8.getConj()) << endl;
	cout << "|c8| = |-1 + 3i| = " << static_cast<Frac>(c8.getAbs()) << endl << endl;

	Complex c9(3, 4);
	cout << "c9 == c7* ==> " << c9 << " == " << c7.getConj() << " ==> " << boolalpha << c9.equals(c7.getConj()) << endl;
	cout << "c8 != c7* ==> " << c8 << " != " << c7.getConj() << " ==> " << boolalpha << c8.neq(c7.getConj()) << endl;

	return 0;
}