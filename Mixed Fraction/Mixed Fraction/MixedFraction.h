#pragma once
#include "Fraction.h"
class MixedFraction : public Fraction
{
public:
	MixedFraction(int _num, int _den, int _whole);
	MixedFraction(const MixedFraction& par); 

	int getWhole();	//자연수 반환
	int getNumer();	// 허수부 반환
	int getDenom();	// 크기(절대값)

	Fraction getFrac();	//지분수 부분 반환
	Fraction toFrac();	// 가분수 변환

	void show();

public : 
	MixedFraction& add(const MixedFraction& rval);
	MixedFraction& sub(const MixedFraction& rval);
	MixedFraction& mul(const MixedFraction& rval);
	MixedFraction& div(const MixedFraction& rval);

	static MixedFraction add(const MixedFraction& rval,const MixedFraction&lval);
	static MixedFraction sub(const MixedFraction& rval, const MixedFraction& lval);
	static MixedFraction mul(const MixedFraction& rval, const MixedFraction& lval);
	static MixedFraction div(const MixedFraction& rval, const MixedFraction& lval);
private:
	void cancel();
	static int euclidGcd(int lval, int rval);
	static int myLcm(int lval, int rval);
private:
	int whole;
};

