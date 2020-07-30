#pragma once

#include "Draw_XY.h"
#include "Fourier_Transform.h"

#include <math.h>

class Digital_Filter
{
public:
	Digital_Filter(void);
	~Digital_Filter(void);
	void Digital_Filter_LowPass();
	void Digital_Filter_Butterworth();
	void Digital_Filter_Chebyshev();
	void Digital_Filter_FilterValue(CDC* pDC);

public:
	CString N;	//필터 차수를 화면에 나타낼 변수
	CString Cf;	//차단주파수를 화면에 나타낼 변수
	Fourier_Transform fourier;
	Fourier_Transform inverse_fourier;

	int Data_No;
	int m_Filter_Order;		//필터 차수
	int m_Filter_CutOff;	//차단주파수

	//필터
	double LowPass_Filter[Total_No];		//저역통과
	double Butterworth_Filter[Total_No];	//버터워스
	double Chebyshev_Filter[Total_No];		//체비셰브

	//필터를 시간축 상 함수로 나타낼 변수
	double LowPass_TimeDomain[Total_No]; 
	double Butterworth_TimeDomain[Total_No];
	double Chebyshev_TimeDomain[Total_No];
	
};