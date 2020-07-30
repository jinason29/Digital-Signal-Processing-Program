#pragma once

#define Total_No 1024

class Draw_Signal
{
public:
	Draw_Signal(void);
	~Draw_Signal(void);
	void Draw_Signal::Signal_View(CDC* pDC, int start_x, int start_y);
public:
	int Data_No;
	int M;

	double Display_Data[Total_No];
};