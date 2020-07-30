#include "stdafx.h"
#include "Draw_Signal.h"

Draw_Signal::Draw_Signal(void)
	: Data_No(0)
	, M(100)
{
	for(int t=0; t<Total_No; t++)
		Display_Data[t]=0;
}

Draw_Signal::~Draw_Signal(void)
{
}

//화면에 파형을 그리는 함수
void Draw_Signal::Signal_View(CDC* pDC, int start_x, int start_y)
{
	CPen pen(PS_SOLID, 1, RGB(100,100,200));
	CPen *pOldPen = pDC->SelectObject(&pen);

	for(int t=0; t<Data_No; t++){
		pDC->MoveTo(start_x+t, start_y);
		pDC->LineTo(start_x+t, start_y-Display_Data[t]*M);
	}
	pDC->SelectObject(pOldPen);
}