#pragma once

#include <math.h>

#define Pi 3.141592
#define Total_No 1024

class Set_Signal
{
public:
	Set_Signal(void);
	~Set_Signal(void);
	void Signal_Data();

public:
	CString m_Signal_Flag;

	int	Data_No;
	int m_Signal_Freq;

	double Sin_Signal[Total_No]; 
	double Cos_Signal[Total_No];
	double Sinc_Signal[Total_No];
	double WhiteNoise_Signal[Total_No];
};

