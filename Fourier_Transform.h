#pragma once

#include <math.h>

#define Total_No 1024
#define Pi 3.141592

class Fourier_Transform
{
public:
	Fourier_Transform(void);
	~Fourier_Transform(void);
	void FT_Cal();

public:
	int Data_No;
	double Input_Signal[Total_No];
	double FT_Sin[Total_No];
	double FT_Cos[Total_No];
	double FT_Transform[Total_No];
};