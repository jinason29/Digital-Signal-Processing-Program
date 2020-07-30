#include "stdafx.h"
#include "AdjMax.h"

AdjMax::AdjMax(void)
{
	AdMax = new double[Total_No];
	for(int i=0; i<Total_No; i++){
		AdMax[i] = 0;
	}
}

AdjMax::~AdjMax(void)
{
	delete [] AdMax;
}

//데이터 정규화
void AdjMax::Sort_Max(void)
{
	//데이터 중 절대값이 가장 큰 값을 찾는다.
	m_Max = AdMax[0];
	for(int i=1; i<m_TotalData; i++){
		if(m_Max<abs(AdMax[i]))
			m_Max = abs(AdMax[i]);
	}
	//모든 데이터를 절대값이 가장 큰 값으로 나눈다.
	//절대값이 가장 큰 값은 1이 된다.
	for(int i=0; i<m_TotalData; i++){
		AdMax[i] = AdMax[i]/m_Max;
	}
}