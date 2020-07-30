#include "stdafx.h"
#include "Fourier_Transform.h"

Fourier_Transform::Fourier_Transform(void)
	: Data_No(0)
{
	for(int t=0; t<Total_No; t++){
		Input_Signal[t] = 0;
		FT_Sin[t]=0;
		FT_Cos[t]=0;
		FT_Transform[t]=0;
	}
}

Fourier_Transform::~Fourier_Transform(void)
{
}

//푸리에 트랜스폼_주파수 변환
void Fourier_Transform::FT_Cal()
{
	for(int t=0; t<Data_No; t++){
		FT_Sin[t]=0;
		FT_Cos[t]=0;
		for(int n=0;n<Data_No; n++){
			FT_Sin[t]+=(Input_Signal[n]*sin((2*Pi*n/Data_No)*t));
			FT_Cos[t]+=(Input_Signal[n]*cos((2*Pi*n/Data_No)*t));
		}
		FT_Transform[t]=sqrt((FT_Sin[t]*FT_Sin[t])+(FT_Cos[t]*FT_Cos[t]));
	}
	/*
	for(int f=0; f<Data_No/2; f++){
		FT_Transform[f] = 2*FT_Transform[f];
	}
	*/
}