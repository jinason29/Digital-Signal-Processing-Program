
// JungSangE_DSPView.h : CJungSangE_DSPView 클래스의 인터페이스
//

#pragma once

#include "AdjMax.h"
#include "Draw_XY.h"
#include "Draw_Signal.h"
#include "Input_Signal.h"
#include "Convolution.h"
#include "Set_Signal.h"
#include "Fourier_Transform.h"
#include "Correlation.h"
#include "Set_Filter.h"
#include "Digital_Filter.h"

#include <math.h>

#define Total_Data 1024
#define Pie 3.141592
#define Signal_Box 5

class CJungSangE_DSPView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CJungSangE_DSPView();
	DECLARE_DYNCREATE(CJungSangE_DSPView)

// 특성입니다.
public:
	CJungSangE_DSPDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CJungSangE_DSPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	Draw_XY draw_xy;
	Draw_Signal draw_signal;
	AdjMax adjmax;
	Set_Signal set_signal;
	Convolution convolution;
	Fourier_Transform fourier_transform;
	Correlation correlation;
	CSet_Filter set_filter;
	Digital_Filter digital_filter;

	CString Time_Mode;
	CString Freq_Mode;
	CString Text;
	CString Hz;
	CString Size;
	CString InputSignal;

	CString m_DF_Filter_Flag;

	afx_msg void OnConvxt();
	afx_msg void OnConvht();
	afx_msg void OnConvyt();
	afx_msg void OnFtInput();
	afx_msg void OnFtInputreset();
	afx_msg void OnFtFourier();
	afx_msg void OnCorAutoInput();
	afx_msg void OnCorCrossInput1();
	afx_msg void OnCorCrossInput2();
	afx_msg void OnCorOutput();
	afx_msg void OnDfInputadd();
	afx_msg void OnDfInputreset();
	afx_msg void OnDfSetfilter();
	afx_msg void OnDfFilterreset();
	afx_msg void OnDfOutput();
	afx_msg void OnAllreset();

	int m_DF_Filter_Order;
	int m_DF_Filter_CutOff;
	
	double Add_Signal[Total_Data];
	double Time_Signal1[Total_Data];
	double Time_Signal2[Total_Data];
	double Time_Signal3[Total_Data];
	double Freq_Signal1[Total_Data];
	double Freq_Signal2[Total_Data];
	double Freq_Signal3[Total_Data];
	
	void Display_Time_Signal(CDC* pDC);
	void Display_Freq_Signal(CDC* pDC);
	
	struct{
		CString Signal_Flag[Signal_Box];
		int Signal_Freq[Signal_Box];
	}Input1, Input2;
};



#ifndef _DEBUG  // JungSangE_DSPView.cpp의 디버그 버전
inline CJungSangE_DSPDoc* CJungSangE_DSPView::GetDocument() const
   { return reinterpret_cast<CJungSangE_DSPDoc*>(m_pDocument); }
#endif

