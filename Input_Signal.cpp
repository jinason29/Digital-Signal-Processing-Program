// ConvInput.cpp : 구현 파일입니다.

#include "stdafx.h"
#include "Input_Signal.h"

// CInput_Signal 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInput_Signal, CDialog)

CInput_Signal::CInput_Signal(CWnd* pParent /*=NULL*/)
	: CDialog(CInput_Signal::IDD, pParent)
	, m_InputSignal_Freq(1)
	, m_InputSignal_Flag(_T("Sin"))
	, InputSignal_Select_Flag(0)
{

}

CInput_Signal::~CInput_Signal()
{
}

void CInput_Signal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_InputSignal_Freq, m_InputSignal_Freq);
	DDX_Radio(pDX, IDC_InputSignal_Sin, InputSignal_Select_Flag);
}


BEGIN_MESSAGE_MAP(CInput_Signal, CDialog)

	ON_BN_CLICKED(IDOK, &CInput_Signal::OnBnClickedOk)
END_MESSAGE_MAP()


// CConvInput 메시지 처리기입니다.


//확인 버튼을 누르면 입력신호를 화면에 나타낸다. 
void CInput_Signal::OnBnClickedOk()
{
	UpdateData(TRUE);
	CString message;

	switch(InputSignal_Select_Flag){

	case 0:
		m_InputSignal_Flag = "Sin";
		message.Format(_T(" Sin, 주파수 %dHz가 생성되었습니다.\n"), m_InputSignal_Freq);
		AfxMessageBox(message);
		break;
	case 1:
		m_InputSignal_Flag = "Cos";
		message.Format(_T(" Cos, 주파수 %dHz가 생성되었습니다.\n"), m_InputSignal_Freq);
		AfxMessageBox(message);
		break;
	case 2:
		m_InputSignal_Flag = "Sinc";
		message.Format(_T(" Sinc, 주파수 %dHz가 생성되었습니다.\n"), m_InputSignal_Freq);
		AfxMessageBox(message);
		break;
	case 3:
		m_InputSignal_Flag = "White Noise";
		message.Format(_T(" White Noise가 생성되었습니다."));
		AfxMessageBox(message);
		break;
	}

	CDialog::OnOK();
}
