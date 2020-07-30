#include "stdafx.h"
#include "Draw_XY.h"

Draw_XY::Draw_XY(void)
{
}

Draw_XY::~Draw_XY(void)
{
}

//화면에 틀을 그리는 함수
void Draw_XY::XY_View(CDC* pDC)
{
	pDC->Rectangle(TimeX1_Start, TimeY1_Start, TimeX1_End, TimeY1_End);
	pDC->MoveTo(TimeX1_Start, TimeY1);
	pDC->LineTo(TimeX1_End, TimeY1);

	pDC->Rectangle(TimeX2_Start, TimeY2_Start, TimeX2_End, TimeY2_End);
	pDC->MoveTo(TimeX2_Start, TimeY2);
	pDC->LineTo(TimeX2_End, TimeY2);

	pDC->Rectangle(TimeX3_Start, TimeY3_Start, TimeX3_End, TimeY3_End);
	pDC->MoveTo(TimeX3_Start, TimeY3);
	pDC->LineTo(TimeX3_End, TimeY3);

	pDC->Rectangle(FreqX1_Start, FreqY1_Start, FreqX1_End, FreqY1_End);
	pDC->MoveTo(FreqX1_Start, FreqY1);
	pDC->LineTo(FreqX1_End, FreqY1);

	pDC->Rectangle(FreqX2_Start, FreqY2_Start, FreqX2_End, FreqY2_End);
	pDC->MoveTo(FreqX2_Start, FreqY2);
	pDC->LineTo(FreqX2_End, FreqY2);

	pDC->Rectangle(FreqX3_Start, FreqY3_Start, FreqX3_End, FreqY3_End);
	pDC->MoveTo(FreqX3_Start, FreqY3);
	pDC->LineTo(FreqX3_End, FreqY3);
}