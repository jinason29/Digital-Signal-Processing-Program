#pragma once


// CSet_Filter 대화 상자입니다.

class CSet_Filter : public CDialog
{
	DECLARE_DYNAMIC(CSet_Filter)

public:
	CSet_Filter(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSet_Filter();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_Set_Filter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_SetFilter_Flag;

	int m_SetFilter_Order;
	int m_SetFilter_CutOff;
	int Filter_Select_Flag;

	afx_msg void OnBnClickedOk();
};
