#include "stdafx.h"
#include "Set_Signal.h"

Set_Signal::Set_Signal(void)
	: m_Signal_Flag(_T(""))
	, Data_No(Total_No)
	, m_Signal_Freq(1)
{
	for(int t=0; t<Data_No; t++){
		Sin_Signal[t] = 0;
		Cos_Signal[t] = 0;
		Sinc_Signal[t] = 0;
		WhiteNoise_Signal[t] =0;
	}
}

Set_Signal::~Set_Signal(void)
{
}

void Set_Signal::Signal_Data()
{
	int	t;
	if(m_Signal_Flag == "Sin"){
		for(t=0; t<Data_No; t++)
			Sin_Signal[t] = sin((2*Pi*m_Signal_Freq/Data_No)*t);
	}
	else if(m_Signal_Flag == "Cos") {
		for(t=0; t<Data_No ; t++)
			Cos_Signal[t] = cos((2*Pi*m_Signal_Freq/Data_No)*t);
	}
	else if(m_Signal_Flag == "Sinc"){
		for(int i=0; i<Data_No; i++)
			Sinc_Signal[i] = sin((Pi*i*m_Signal_Freq)/Data_No)/((Pi*i)/Data_No);

		Sinc_Signal[0] = Sinc_Signal[1];
	}
	else if(m_Signal_Flag == "White Noise"){
		int RandNo;
		for(int i=0; i<Data_No; i++){
			RandNo = rand()%100-50;
			WhiteNoise_Signal[i] = double(RandNo)/50;
		}
	}
}
