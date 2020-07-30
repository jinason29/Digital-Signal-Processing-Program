#include "stdafx.h"
#include "Convolution.h"

Convolution::Convolution(void)
	: m_Co_Data1(0)
	, m_Co_Data2(0)
{
	m_InData1=new double[Total_No];
	m_InData2=new double[Total_No];
	m_OutData=new double[Total_No*2];
	for(int i=0; i<Total_No; i++){
		m_InData1[i]=m_InData2[i]=0;
	}
	for(int i=0; i<Total_No*2; i++){
		m_OutData[i]=0;
	}
}

Convolution::~Convolution(void)
{
	delete []m_InData1;
	delete []m_InData2;
	delete []m_OutData;
}

//Convolution
void Convolution::ConVol(void)
{
	//컨볼루션 결과의 범위는 두 연산함수의 범위의 합이다.
	for(int n=0; n<(m_Co_Data1+m_Co_Data2); n++){
		m_OutData[n]=0;
		for(int k=0; k<=n; k++){
			//컨볼루션 연산
			m_OutData[n] += m_InData1[k]*m_InData2[n-k];
		}
	}
}