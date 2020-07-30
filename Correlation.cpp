#include "stdafx.h"
#include "Correlation.h"

#define	Total_No 1024

Correlation::Correlation(void)
	: m_Co_Data1(0)
	, m_Co_Data2(0)
{
	m_InData1=new double[Total_No];
	m_InData2=new double[Total_No];
	m_OutData=new double[Total_No];
	for(int i=0; i<Total_No; i++)
		m_InData1[i]=m_InData2[i]=m_OutData[i]=0;
}

Correlation::~Correlation(void)
{
	delete []m_InData1;
	delete []m_InData2;
	delete []m_OutData;
}

//Correlation
void Correlation::CorRel(void)
{
	for(int k=0; k<m_Co_Data1; k++){
		m_OutData[k]=0;
		for(int n=k; n<m_Co_Data2; n++){
			m_OutData[k] += m_InData1[n]*m_InData2[n-k];
		}
	}	
}
