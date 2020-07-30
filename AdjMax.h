#pragma once

#include <math.h>

#define Total_No 1024

class AdjMax
{
public:
	double *AdMax;
	double m_Max;
	int m_TotalData;
public:
	AdjMax(void);
	~AdjMax(void);
	void Sort_Max(void);
};