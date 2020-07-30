#pragma once

#define Depth 360
#define Total_No 1024

#define TimeX1_Start 50
#define TimeY1_Start 50
#define TimeX1_End	TimeX1_Start+Total_No
#define TimeY1_End	TimeY1_Start+Depth

#define TimeX2_Start TimeX1_Start
#define TimeY2_Start TimeY1_End+50
#define TimeX2_End	TimeX2_Start+Total_No
#define TimeY2_End	TimeY2_Start+Depth

#define TimeX3_Start TimeX2_Start
#define TimeY3_Start TimeY2_End+50
#define TimeX3_End	TimeX3_Start+Total_No
#define TimeY3_End	TimeY3_Start+Depth

#define FreqX1_Start TimeX1_End+50
#define FreqY1_Start TimeY1_Start
#define FreqX1_End FreqX1_Start+Total_No
#define FreqY1_End FreqY1_Start+Depth

#define FreqX2_Start FreqX1_Start
#define FreqY2_Start FreqY1_End+50
#define FreqX2_End FreqX2_Start+Total_No
#define FreqY2_End FreqY2_Start+Depth

#define FreqX3_Start FreqX2_Start
#define FreqY3_Start FreqY2_End+50
#define FreqX3_End FreqX3_Start+Total_No
#define FreqY3_End FreqY3_Start+Depth

#define TimeX TimeX1_Start
#define TimeY1 TimeY1_Start+(Depth/2)
#define TimeY2 TimeY2_Start+(Depth/2)
#define TimeY3 TimeY3_Start+(Depth/2)
#define FreqX FreqX1_Start
#define FreqY1 FreqY1_Start+(Depth/2)
#define FreqY2 FreqY2_Start+(Depth/2)
#define FreqY3 FreqY3_Start+(Depth/2)

#define TextTimeX 50
#define TextTimeY1 25
#define TextTimeY2 TextTimeY1+TextTimeX+Depth
#define TextTimeY3 TextTimeY1+(2*TextTimeX)+(2*Depth)
#define TextFreqX (2*TextTimeX)+Total_No
#define TextFreqY1 25
#define TextFreqY2 TextTimeY2
#define TextFreqY3 TextTimeY3

class Draw_XY
{
public:
	Draw_XY(void);
	~Draw_XY(void);

	void XY_View(CDC* pDC);
};