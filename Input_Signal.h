#pragma once

#include "JungSangE_DSP.h"
#include "afxdialogex.h"

// CInput_Signal 대화 상자입니다.

class CInput_Signal : public CDialog
{
	DECLARE_DYNAMIC(CInput_Signal)

public:
	CInput_Signal(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInput_Signal();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_Input_Signal };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_InputSignal_Flag;

	int m_InputSignal_Freq;
	int InputSignal_Select_Flag;
	
	afx_msg void OnBnClickedOk();
};
