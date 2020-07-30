#pragma once

#define	Total_No 1024

class Convolution
{
public:
	int m_Co_Data1, m_Co_Data2;
	double	*m_InData1, *m_InData2;
	double	*m_OutData;
public:
	Convolution(void);
	~Convolution(void);
public:
	void ConVol(void);
};
