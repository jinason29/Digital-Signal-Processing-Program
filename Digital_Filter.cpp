#include "stdafx.h"
#include "Digital_Filter.h"

Digital_Filter::Digital_Filter(void)
	: N(_T(""))
	, Cf(_T(""))
	, Data_No(0)
	, m_Filter_Order(1)
	, m_Filter_CutOff(1)
{
	for(int i=0; i<Total_No; i++){
		LowPass_Filter[i] = 0;
		Butterworth_Filter[i] = 0;
		Chebyshev_Filter[i] = 0;
		LowPass_TimeDomain[i] = 0;
		Butterworth_TimeDomain[i] = 0;
		Chebyshev_TimeDomain[i] = 0;
	}
}

Digital_Filter::~Digital_Filter(void)
{
}

//acosh 함수
double acosh(double x){
	double y;
	y = log(x + sqrt((x*x)-1));

	return y;
}

//저역통과 필터
void Digital_Filter::Digital_Filter_LowPass()
{
	for(int t=0; t<Data_No; t++)
			LowPass_TimeDomain[t] = 0;
	//시간축 상에서 Sinc함수를 이용하여 저역통과 필터를 만든다. 
	for(int t=m_Filter_Order; t<Data_No; t++)
		LowPass_TimeDomain[t] = abs(sin((Pi*t*m_Filter_CutOff)/Data_No)/((Pi*t)/Data_No));
	LowPass_TimeDomain[0] = LowPass_TimeDomain[1];

	//푸리에 트랜스폼 하여 주파수 상에서 저역통과 필터를 나타낸다.
	fourier.Data_No = Data_No;
	for(int t=0; t<Data_No; t++)
		fourier.Input_Signal[t] = LowPass_TimeDomain[t];
	fourier.FT_Cal();
	for(int f=0; f<Data_No; f++)
		LowPass_Filter[f] = fourier.FT_Transform[f];
}

//버터워스 필터
void Digital_Filter::Digital_Filter_Butterworth()
{
	for(int f=0; f<Data_No ; f++){
		double W_Wc_2n = 0;
		Butterworth_Filter[f] = 0;

		//주파수 상에서 버터워스 필터를 구현한다.
		W_Wc_2n = pow((double)(2*Pi*f)/(2*Pi*m_Filter_CutOff), 2*m_Filter_Order);
		Butterworth_Filter[f] = 1/sqrt(1+W_Wc_2n);
	}
	//역 푸리에 트랜스폼 하여 시간축 상에서 버터워스 필터를 나타낸다.
	inverse_fourier.Data_No = Data_No;
	for(int f=0; f<Data_No; f++)
		inverse_fourier.Input_Signal[f] = Butterworth_Filter[f];
	inverse_fourier.FT_Cal();
	for(int t=0; t<Data_No; t++)
		Butterworth_TimeDomain[t] = inverse_fourier.FT_Transform[t];
	/*
	for(int t=0; t<Data_No/2; t++)
		Butterworth_TimeDomain[t] = inverse_fourier.FT_Transform[t] + inverse_fourier.FT_Transform[(Data_No-1)-t];
	for(int t=(Data_No-1); t<Data_No; t++)
		Butterworth_TimeDomain[t] = 0;
	*/
}

//체비셰브 필터
void Digital_Filter::Digital_Filter_Chebyshev()
{
	for(int f=0; f<Data_No; f++){
		double epsilon = 0.5;
		double Cn = 0;
		double W_Wc = 0;
		Chebyshev_Filter[f] = 0;

		//주파수 상에서 체비셰브 필터를 구현한다.
		W_Wc = (double)((2*Pi*f)/(2*Pi*m_Filter_CutOff));
		if(fabs(W_Wc) <= 1)
			Cn = cos((double)m_Filter_Order*(acos(W_Wc)));
		else if(fabs(W_Wc) > 1)
			Cn = cosh((double)m_Filter_Order*(acosh(W_Wc)));
		Chebyshev_Filter[f] = fabs(1/sqrt(1+(pow(epsilon, 2)*pow(Cn, 2))));
	}
	//역 푸리에 트랜스폼 하여 시간축 상에서 체비셰브 필터를 나타낸다.
	inverse_fourier.Data_No = Data_No;
	for(int f=0; f<Data_No; f++)
		inverse_fourier.Input_Signal[f] = Chebyshev_Filter[f];
	inverse_fourier.FT_Cal();
	for(int t=0; t<Data_No; t++)
		Chebyshev_TimeDomain[t] = inverse_fourier.FT_Transform[t];
}

//필터의 정보를 알려주는 함수
void Digital_Filter::Digital_Filter_FilterValue(CDC* pDC)
{
	// 입력된 필터차수를 표시한다.
	N.Format(_T("필터차수(N) = %d"), m_Filter_Order);
	pDC->TextOut(FreqX+20, FreqY2_Start+20, N);

	// 입력된 차단주파수를 표시한다.
	Cf.Format(_T("차단주파수(Cf) = %d"), m_Filter_CutOff);
	pDC->TextOut(FreqX+20, FreqY2_Start+50, Cf);

	// 주파수 상 필터일 때
	for(int f=0; f<Data_No; f++){
		// 차단주파수를 화면에 표시한다.(차단주파수가 0일때 제외)
		if((f == m_Filter_CutOff)&&(m_Filter_CutOff != 0)){
			int x = FreqX+f, y = FreqY2+10;
			Cf.Format(_T("%dHz"),f);
			pDC->TextOut(x,y,Cf);
		}
	}
}