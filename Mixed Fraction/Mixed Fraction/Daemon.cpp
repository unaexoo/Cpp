#include<iostream>
#include"Rational.h"
#include"Fraction.h"
#include"MixedFraction.h"
using namespace std;
int main() {
	Fraction f1(5, 4);
	Fraction f2(1, 4);

	cout << "f3 : ";
	Fraction f3 = Fraction::add(f1, f2);
	f3.show();
	cout << endl;

	// ´ëºÐ¼ö
	MixedFraction m1(5, 4, 1);
	
	MixedFraction m2(1, 4, 0);

	MixedFraction m3 = MixedFraction::add(m1, m2);
	m3.show();
	m1.add(m2);
	cout << endl;
	m1.show();
}