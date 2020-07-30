// Set_Filter.cpp : 구현 파일입니다.

#include "stdafx.h"
#include "JungSangE_DSP.h"
#include "Set_Filter.h"
#include "afxdialogex.h"


// CSet_Filter 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSet_Filter, CDialog)

CSet_Filter::CSet_Filter(CWnd* pParent /*=NULL*/)
	: CDialog(CSet_Filter::IDD, pParent)
	, m_SetFilter_Flag(_T(""))
	, m_SetFilter_Order(1)
	, m_SetFilter_CutOff(1)
	, Filter_Select_Flag(0)
{

}

CSet_Filter::~CSet_Filter()
{
}

void CSet_Filter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SetFilter_Order, m_SetFilter_Order);
	DDX_Text(pDX, IDC_SetFilter_CutOff, m_SetFilter_CutOff);
	DDX_Radio(pDX, IDC_SetFilter_LowPass, Filter_Select_Flag);
}


BEGIN_MESSAGE_MAP(CSet_Filter, CDialog)
	ON_BN_CLICKED(IDOK, &CSet_Filter::OnBnClickedOk)
END_MESSAGE_MAP()


// CSet_Filter 메시지 처리기입니다.

//확인 버튼을 누르면 설정한 필터를 화면에 나타낸다.
void CSet_Filter::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	CString message;

	switch(Filter_Select_Flag){

	case 0:
		m_SetFilter_Flag = "Low Pass";
		message.Format(_T(" Low Pass, 필터차수 %d 차단주파수 %dHz가 생성되었습니다."), m_SetFilter_Order, m_SetFilter_CutOff);
		AfxMessageBox(message);
		break;
	case 1:
		m_SetFilter_Flag = "Butterworth";
		message.Format(_T(" Butterworth, 필터차수 %d 차단주파수 %dHz가 생성되었습니다."), m_SetFilter_Order, m_SetFilter_CutOff);
		AfxMessageBox(message);
		break;
	case 2:
		m_SetFilter_Flag = "Chebyshev";
		message.Format(_T(" Chebyshev, 필터차수 %d 차단주파수 %dHz가 생성되었습니다."), m_SetFilter_Order, m_SetFilter_CutOff);
		AfxMessageBox(message);
		break;
	}

	CDialog::OnOK();
}
