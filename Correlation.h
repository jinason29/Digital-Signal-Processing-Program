#pragma once

class Correlation
{
public:
	int m_Co_Data1, m_Co_Data2;
	double	*m_InData1, *m_InData2;
	double	*m_OutData;
public:
	Correlation(void);
	~Correlation(void);

	void CorRel(void);
};