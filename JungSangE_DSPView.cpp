
// JungSangE_DSPView.cpp : CJungSangE_DSPView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "JungSangE_DSP.h"
#endif

#include "JungSangE_DSPDoc.h"
#include "JungSangE_DSPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CJungSangE_DSPView

IMPLEMENT_DYNCREATE(CJungSangE_DSPView, CScrollView)

BEGIN_MESSAGE_MAP(CJungSangE_DSPView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CJungSangE_DSPView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Conv_xt, &CJungSangE_DSPView::OnConvxt)
	ON_COMMAND(ID_Conv_ht, &CJungSangE_DSPView::OnConvht)
	ON_COMMAND(ID_Conv_yt, &CJungSangE_DSPView::OnConvyt)
	ON_COMMAND(ID_FT_Input, &CJungSangE_DSPView::OnFtInput)
	ON_COMMAND(ID_FT_InputReset, &CJungSangE_DSPView::OnFtInputreset)
	ON_COMMAND(ID_FT_Fourier, &CJungSangE_DSPView::OnFtFourier)
	ON_COMMAND(ID_Cor_Auto_Input, &CJungSangE_DSPView::OnCorAutoInput)
	ON_COMMAND(ID_Cor_Cross_Input1, &CJungSangE_DSPView::OnCorCrossInput1)
	ON_COMMAND(ID_Cor_Cross_Input2, &CJungSangE_DSPView::OnCorCrossInput2)
	ON_COMMAND(ID_Cor_Output, &CJungSangE_DSPView::OnCorOutput)
	ON_COMMAND(ID_DF_InputAdd, &CJungSangE_DSPView::OnDfInputadd)
	ON_COMMAND(ID_DF_InputReset, &CJungSangE_DSPView::OnDfInputreset)
	ON_COMMAND(ID_DF_SetFilter, &CJungSangE_DSPView::OnDfSetfilter)
	ON_COMMAND(ID_DF_FilterReset, &CJungSangE_DSPView::OnDfFilterreset)
	ON_COMMAND(ID_DF_Output, &CJungSangE_DSPView::OnDfOutput)
	ON_COMMAND(ID_AllReset, &CJungSangE_DSPView::OnAllreset)
END_MESSAGE_MAP()

// CJungSangE_DSPView 생성/소멸

CJungSangE_DSPView::CJungSangE_DSPView()
	: Time_Mode(_T(""))
	, Freq_Mode(_T(""))
	, Text(_T(""))
	, m_DF_Filter_Flag(_T(""))
	, m_DF_Filter_Order(1)
	, m_DF_Filter_CutOff(1)
	
{
	// TODO: 여기에 생성 코드를 추가합니다.

	for(int i=0; i<Total_Data; i++){
		Add_Signal[i] = 0;
		Time_Signal1[i] = 0;
		Time_Signal2[i] = 0;
		Time_Signal3[i] = 0;
		Freq_Signal1[i] = 0;
		Freq_Signal2[i] = 0;
		Freq_Signal3[i] = 0;
	}
	for(int i=0; i<Signal_Box; i++){
		Input1.Signal_Flag[i] = "";
		Input1.Signal_Freq[i] = 1;
		Input2.Signal_Flag[i] = "";
		Input2.Signal_Freq[i] = 1;
	}
}

CJungSangE_DSPView::~CJungSangE_DSPView()
{
}

BOOL CJungSangE_DSPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CJungSangE_DSPView 그리기

void CJungSangE_DSPView::OnDraw(CDC* pDC)
{
	CJungSangE_DSPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	draw_xy.XY_View(pDC);

	Display_Time_Signal(pDC);
	Display_Freq_Signal(pDC);
}

void CJungSangE_DSPView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2200;
	sizeTotal.cy = 1500;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CJungSangE_DSPView 인쇄


void CJungSangE_DSPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CJungSangE_DSPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CJungSangE_DSPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CJungSangE_DSPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CJungSangE_DSPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CJungSangE_DSPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CJungSangE_DSPView 진단

#ifdef _DEBUG
void CJungSangE_DSPView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CJungSangE_DSPView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CJungSangE_DSPDoc* CJungSangE_DSPView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJungSangE_DSPDoc)));
	return (CJungSangE_DSPDoc*)m_pDocument;
}
#endif //_DEBUG


// CJungSangE_DSPView 메시지 처리기


void CJungSangE_DSPView::OnConvxt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CInput_Signal convolution_xt;
	
	if(Time_Mode != "Convolution"){
		for(int i=0; i<Signal_Box; i++){
			Input1.Signal_Flag[i] = "";
			Input1.Signal_Freq[i] = 1;
			Input2.Signal_Flag[i] = "";
			Input2.Signal_Freq[i] = 1;
		}
	}

	for(int i=0; i<Signal_Box; i++){
		if(i==(Signal_Box-1)){
			convolution_xt.m_InputSignal_Flag = Input1.Signal_Flag[i];
			convolution_xt.m_InputSignal_Freq = Input1.Signal_Freq[i];
			break;
		}else if(Input1.Signal_Flag[i+1]==""){
			convolution_xt.m_InputSignal_Flag = Input1.Signal_Flag[i];
			convolution_xt.m_InputSignal_Freq = Input1.Signal_Freq[i];
			break;
		}
	}
	
	if(convolution_xt.DoModal() == IDOK){
		for(int i=0; i<Total_Data; i++){
			if(Time_Mode == "Convolution"){
				break;
			}else{
				Time_Signal1[i] = 0;
				Time_Signal2[i] = 0;
				Time_Signal3[i] = 0;
				Freq_Signal1[i] = 0;
				Freq_Signal2[i] = 0;
				Freq_Signal3[i] = 0;
			}
		}
		Time_Mode = "Convolution";
		Freq_Mode = "";
		
		set_signal.Data_No = Total_Data;
		for(int i=0; i<Signal_Box; i++){
			if(Input1.Signal_Flag[i]==""){
				Input1.Signal_Flag[i] = convolution_xt.m_InputSignal_Flag;
				Input1.Signal_Freq[i] = convolution_xt.m_InputSignal_Freq;
			
				set_signal.m_Signal_Flag = Input1.Signal_Flag[i];
				set_signal.m_Signal_Freq = Input1.Signal_Freq[i];
				set_signal.Signal_Data();

				if(Input1.Signal_Flag[i] == "Sin"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sin_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "Cos"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Cos_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "Sinc"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sinc_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "White Noise"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.WhiteNoise_Signal[t];
				}
				for(int t=0; t<Total_Data; t++){
					Time_Signal1[t] += Add_Signal[t];
				}
				break;
			}
		}
	}
	Invalidate();
}

void CJungSangE_DSPView::OnConvht()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CInput_Signal convolution_ht;
	
	if(Time_Mode != "Convolution"){
		for(int i=0; i<Signal_Box; i++){
			Input1.Signal_Flag[i] = "";
			Input1.Signal_Freq[i] = 1;
			Input2.Signal_Flag[i] = "";
			Input2.Signal_Freq[i] = 1;
		}
	}

	for(int i=0; i<Signal_Box; i++){
		if(i==(Signal_Box-1)){
			convolution_ht.m_InputSignal_Flag = Input2.Signal_Flag[i];
			convolution_ht.m_InputSignal_Freq = Input2.Signal_Freq[i];
			break;
		}else if(Input2.Signal_Flag[i+1]==""){
			convolution_ht.m_InputSignal_Flag = Input2.Signal_Flag[i];
			convolution_ht.m_InputSignal_Freq = Input2.Signal_Freq[i];
			break;
		}
	}
	
	if(convolution_ht.DoModal() == IDOK){
		for(int i=0; i<Total_Data; i++){
			if(Time_Mode == "Convolution"){
				break;
			}else{
				Time_Signal1[i] = 0;
				Time_Signal2[i] = 0;
				Time_Signal3[i] = 0;
				Freq_Signal1[i] = 0;
				Freq_Signal2[i] = 0;
				Freq_Signal3[i] = 0;
			}
		}
		Time_Mode = "Convolution";
		Freq_Mode = "";
		
		set_signal.Data_No = Total_Data;
		for(int i=0; i<Signal_Box; i++){
			if(Input2.Signal_Flag[i]==""){
				Input2.Signal_Flag[i] = convolution_ht.m_InputSignal_Flag;
				Input2.Signal_Freq[i] = convolution_ht.m_InputSignal_Freq;
			
				set_signal.m_Signal_Flag = Input2.Signal_Flag[i];
				set_signal.m_Signal_Freq = Input2.Signal_Freq[i];
				set_signal.Signal_Data();

				if(Input2.Signal_Flag[i] == "Sin"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sin_Signal[t];
				}
				else if(Input2.Signal_Flag[i] == "Cos"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Cos_Signal[t];
				}
				else if(Input2.Signal_Flag[i] == "Sinc"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sinc_Signal[t];
				}
				else if(Input2.Signal_Flag[i] == "White Noise"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.WhiteNoise_Signal[t];
				}
				for(int t=0; t<Total_Data; t++){
					Time_Signal2[t] += Add_Signal[t];
				}
				break;
			}
		}
	}
	Invalidate();
}

void CJungSangE_DSPView::OnConvyt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	convolution.m_Co_Data1=Total_Data;
	convolution.m_Co_Data2=Total_Data;

	for(int x=0; x<convolution.m_Co_Data1; x++)
		convolution.m_InData1[x]=Time_Signal1[x];

	for(int x=0; x<convolution.m_Co_Data2; x++)
		convolution.m_InData2[x]=Time_Signal2[x];

	convolution.ConVol();
	for(int x=0; x<Total_Data; x++)
		Time_Signal3[x]=convolution.m_OutData[x];

	Invalidate();
}

void CJungSangE_DSPView::OnFtInput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CInput_Signal fourier_input;
	
	if(Time_Mode != "Fourier Transform"){
		for(int i=0; i<Signal_Box; i++){
			Input1.Signal_Flag[i] = "";
			Input1.Signal_Freq[i] = 1;
			Input2.Signal_Flag[i] = "";
			Input2.Signal_Freq[i] = 1;
		}
	}

	for(int i=0; i<Signal_Box; i++){
		if(i==(Signal_Box-1)){
			fourier_input.m_InputSignal_Flag = Input1.Signal_Flag[i];
			fourier_input.m_InputSignal_Freq = Input1.Signal_Freq[i];
			break;
		}else if(Input1.Signal_Flag[i+1]==""){
			fourier_input.m_InputSignal_Flag = Input1.Signal_Flag[i];
			fourier_input.m_InputSignal_Freq = Input1.Signal_Freq[i];
			break;
		}
	}
	
	if(fourier_input.DoModal() == IDOK){
		for(int i=0; i<Total_Data; i++){
			if(Time_Mode == "Fourier Transform"){
				break;
			}else{
				Time_Signal1[i] = 0;
				Time_Signal2[i] = 0;
				Time_Signal3[i] = 0;
				Freq_Signal1[i] = 0;
				Freq_Signal2[i] = 0;
				Freq_Signal3[i] = 0;
			}
		}
		Time_Mode = "Fourier Transform";
		Freq_Mode = "";
		
		set_signal.Data_No = Total_Data;
		for(int i=0; i<Signal_Box; i++){
			if(Input1.Signal_Flag[i]==""){
				Input1.Signal_Flag[i] = fourier_input.m_InputSignal_Flag;
				Input1.Signal_Freq[i] = fourier_input.m_InputSignal_Freq;
			
				set_signal.m_Signal_Flag = Input1.Signal_Flag[i];
				set_signal.m_Signal_Freq = Input1.Signal_Freq[i];
				set_signal.Signal_Data();

				if(Input1.Signal_Flag[i] == "Sin"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sin_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "Cos"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Cos_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "Sinc"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sinc_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "White Noise"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.WhiteNoise_Signal[t];
				}
				for(int t=0; t<Total_Data; t++){
					Time_Signal1[t] += Add_Signal[t];
				}
				break;
			}
		}
	}
	Invalidate();
}

void CJungSangE_DSPView::OnFtInputreset()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for(int i=0; i<Signal_Box; i++){
		Input1.Signal_Flag[i] = "";
		Input1.Signal_Freq[i] = 1;
	}
	for(int i=0; i<Total_Data; i++){
		Time_Signal1[i] = 0;
		Freq_Signal1[i] = 0;
	}
	Invalidate();
}


void CJungSangE_DSPView::OnFtFourier()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Freq_Mode = "Fourier Transform";

	fourier_transform.Data_No = Total_Data;
	for(int x=0; x<Total_Data; x++)
		fourier_transform.Input_Signal[x] = Time_Signal1[x];
	fourier_transform.FT_Cal();
	for(int x=0; x<Total_Data; x++)
		Freq_Signal1[x] = fourier_transform.FT_Transform[x];

	for(int x=0; x<Total_Data; x++)
		fourier_transform.Input_Signal[x] = Time_Signal2[x];
	fourier_transform.FT_Cal();
	for(int x=0; x<Total_Data; x++)
		Freq_Signal2[x] = fourier_transform.FT_Transform[x];

	for(int x=0; x<Total_Data; x++)
		fourier_transform.Input_Signal[x] = Time_Signal3[x];
	fourier_transform.FT_Cal();
	for(int x=0; x<Total_Data; x++)
		Freq_Signal3[x] = fourier_transform.FT_Transform[x];

	Invalidate();
}

void CJungSangE_DSPView::OnCorAutoInput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CInput_Signal cor_auto;

	if(Time_Mode != "Auto Correlation"){
		for(int i=0; i<Signal_Box; i++){
			Input1.Signal_Flag[i] = "";
			Input1.Signal_Freq[i] = 1;
			Input2.Signal_Flag[i] = "";
			Input2.Signal_Freq[i] = 1;
		}
	}

	for(int i=0; i<Signal_Box; i++){
		if(i==(Signal_Box-1)){
			cor_auto.m_InputSignal_Flag = Input1.Signal_Flag[i];
			cor_auto.m_InputSignal_Freq = Input1.Signal_Freq[i];
			break;
		}else if(Input1.Signal_Flag[i+1]==""){
			cor_auto.m_InputSignal_Flag = Input1.Signal_Flag[i];
			cor_auto.m_InputSignal_Freq = Input1.Signal_Freq[i];
			break;
		}
	}

	if(cor_auto.DoModal() == IDOK){
		for(int i=0; i<Total_Data; i++){
			if(Time_Mode == "Auto Correlation"){
			}else{
				Time_Signal1[i] = 0;
				Time_Signal2[i] = 0;
				Time_Signal3[i] = 0;
				Freq_Signal1[i] = 0;
				Freq_Signal2[i] = 0;
				Freq_Signal3[i] = 0;
			}
		}
		Time_Mode = "Auto Correlation";
		Freq_Mode = "";

		set_signal.Data_No = Total_Data;
		for(int i=0; i<Signal_Box; i++){
			if(Input1.Signal_Flag[i]==""){
				Input1.Signal_Flag[i] = cor_auto.m_InputSignal_Flag;
				Input1.Signal_Freq[i] = cor_auto.m_InputSignal_Freq;
				Input2.Signal_Flag[i] = cor_auto.m_InputSignal_Flag;
				Input2.Signal_Freq[i] = cor_auto.m_InputSignal_Freq;
			
				set_signal.m_Signal_Flag = Input1.Signal_Flag[i];
				set_signal.m_Signal_Freq = Input1.Signal_Freq[i];
				set_signal.Signal_Data();

				if(Input1.Signal_Flag[i] == "Sin"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sin_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "Cos"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Cos_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "Sinc"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sinc_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "White Noise"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.WhiteNoise_Signal[t];
				}
				for(int t=0; t<Total_Data; t++){
					Time_Signal1[t] += Add_Signal[t];
					Time_Signal2[t] += Add_Signal[t];
				}
				break;
			}
		}
	}
	Invalidate();
}

void CJungSangE_DSPView::OnCorCrossInput1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CInput_Signal cor_cross1;
	
	if(Time_Mode != "Cross Correlation"){
		for(int i=0; i<Signal_Box; i++){
			Input1.Signal_Flag[i] = "";
			Input1.Signal_Freq[i] = 1;
			Input2.Signal_Flag[i] = "";
			Input2.Signal_Freq[i] = 1;
		}
	}
	
	for(int i=0; i<Signal_Box; i++){
		if(i==(Signal_Box-1)){
			cor_cross1.m_InputSignal_Flag = Input1.Signal_Flag[i];
			cor_cross1.m_InputSignal_Freq = Input1.Signal_Freq[i];
			break;
		}else if(Input1.Signal_Flag[i+1]==""){
			cor_cross1.m_InputSignal_Flag = Input1.Signal_Flag[i];
			cor_cross1.m_InputSignal_Freq = Input1.Signal_Freq[i];
			break;
		}
	}

	if(cor_cross1.DoModal() == IDOK){
		for(int i=0; i<Total_Data; i++){
			if(Time_Mode == "Cross Correlation"){
				Time_Signal3[i] = 0;
				Freq_Signal3[i] = 0;
			}else{
				Time_Signal1[i] = 0;
				Time_Signal2[i] = 0;
				Time_Signal3[i] = 0;
				Freq_Signal1[i] = 0;
				Freq_Signal2[i] = 0;
				Freq_Signal3[i] = 0;
			}
		}
		Time_Mode = "Cross Correlation";
		Freq_Mode = "";
		
		set_signal.Data_No = Total_Data;
		for(int i=0; i<Signal_Box; i++){
			if(Input1.Signal_Flag[i]==""){
				Input1.Signal_Flag[i] = cor_cross1.m_InputSignal_Flag;
				Input1.Signal_Freq[i] = cor_cross1.m_InputSignal_Freq;
			
				set_signal.m_Signal_Flag = Input1.Signal_Flag[i];
				set_signal.m_Signal_Freq = Input1.Signal_Freq[i];
				set_signal.Signal_Data();

				if(Input1.Signal_Flag[i] == "Sin"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sin_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "Cos"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Cos_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "Sinc"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sinc_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "White Noise"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.WhiteNoise_Signal[t];
				}

				for(int t=0; t<Total_Data; t++){
					Time_Signal1[t] += Add_Signal[t];
				}
				break;
			}
		}
	}
	Invalidate();
}

void CJungSangE_DSPView::OnCorCrossInput2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CInput_Signal cor_cross2;
	
	if(Time_Mode != "Cross Correlation"){
		for(int i=0; i<Signal_Box; i++){
			Input1.Signal_Flag[i] = "";
			Input1.Signal_Freq[i] = 1;
			Input2.Signal_Flag[i] = "";
			Input2.Signal_Freq[i] = 1;
		}
	}

	for(int i=0; i<Signal_Box; i++){
		if(i==(Signal_Box-1)){
			cor_cross2.m_InputSignal_Flag = Input2.Signal_Flag[i];
			cor_cross2.m_InputSignal_Freq = Input2.Signal_Freq[i];
		}else if(Input2.Signal_Flag[i+1]==""){
			cor_cross2.m_InputSignal_Flag = Input2.Signal_Flag[i];
			cor_cross2.m_InputSignal_Freq = Input2.Signal_Freq[i];
			break;
		}
	}

	if(cor_cross2.DoModal() == IDOK){
		for(int i=0; i<Total_Data; i++){
			if(Time_Mode == "Cross Correlation"){
				Time_Signal3[i] = 0;
				Freq_Signal3[i] = 0;
			}else{
				Time_Signal1[i] = 0;
				Time_Signal2[i] = 0;
				Time_Signal3[i] = 0;
				Freq_Signal1[i] = 0;
				Freq_Signal2[i] = 0;
				Freq_Signal3[i] = 0;
			}
		}
		Time_Mode = "Cross Correlation";
		Freq_Mode = "";
		
		set_signal.Data_No = Total_Data;
		for(int i=0; i<Signal_Box; i++){
			if(Input2.Signal_Flag[i]==""){
				Input2.Signal_Flag[i] = cor_cross2.m_InputSignal_Flag;
				Input2.Signal_Freq[i] = cor_cross2.m_InputSignal_Freq;
			
				set_signal.m_Signal_Flag = Input2.Signal_Flag[i];
				set_signal.m_Signal_Freq = Input2.Signal_Freq[i];
				set_signal.Signal_Data();

				if(Input2.Signal_Flag[i] == "Sin"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sin_Signal[t];
				}
				else if(Input2.Signal_Flag[i] == "Cos"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Cos_Signal[t];
				}
				else if(Input2.Signal_Flag[i] == "Sinc"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sinc_Signal[t];
				}
				else if(Input2.Signal_Flag[i] == "White Noise"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.WhiteNoise_Signal[t];
				}

				for(int t=0; t<Total_Data; t++){
					Time_Signal2[t] += Add_Signal[t];
				}
				break;
			}
		}
	}
	Invalidate();
}

void CJungSangE_DSPView::OnCorOutput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	correlation.m_Co_Data1 = Total_Data;
	correlation.m_Co_Data2 = Total_Data;

	for(int x=0; x<Total_Data; x++)
		correlation.m_InData1[x] = Time_Signal1[x];
	for(int x=0; x<Total_Data; x++)
		correlation.m_InData2[x] = Time_Signal2[x];
	correlation.CorRel();
	for(int x=0; x<Total_Data; x++)
		Time_Signal3[x] = correlation.m_OutData[x];

	Invalidate();
}

void CJungSangE_DSPView::OnDfInputadd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CInput_Signal filter;
	
	if(Time_Mode != "Digital Filter"){
		for(int i=0; i<Signal_Box; i++){
			Input1.Signal_Flag[i] = "";
			Input1.Signal_Freq[i] = 1;
		}
	}
	
	for(int i=0; i<Signal_Box; i++){
		if(i==(Signal_Box-1)){
			filter.m_InputSignal_Flag = Input1.Signal_Flag[i];
			filter.m_InputSignal_Freq = Input1.Signal_Freq[i];
			break;
		}else if(Input1.Signal_Flag[i+1]==""){
			filter.m_InputSignal_Flag = Input1.Signal_Flag[i];
			filter.m_InputSignal_Freq = Input1.Signal_Freq[i];
			break;
		}
	}

	if(filter.DoModal() == IDOK){
		for(int i=0; i<Total_Data; i++){
			if(Time_Mode == "Digital Filter"){
				Time_Signal3[i] = 0;
				Freq_Signal3[i] = 0;
			}else{
				if(Freq_Mode == "Digital_Filter"){
					Time_Signal1[i] = 0;
					Time_Signal3[i] = 0;
					Freq_Signal1[i] = 0;
					Freq_Signal3[i] = 0;
				}else{
					Time_Signal1[i] = 0;
					Time_Signal2[i] = 0;
					Time_Signal3[i] = 0;
					Freq_Signal1[i] = 0;
					Freq_Signal2[i] = 0;
					Freq_Signal3[i] = 0;
				}
			}
		}
		Time_Mode = "Digital Filter";
		if(Freq_Mode == "Digital Filter"){}
		else
			Freq_Mode = "";
		
		set_signal.Data_No = Total_Data;
		for(int i=0; i<Signal_Box; i++){
			if(Input1.Signal_Flag[i]==""){
				Input1.Signal_Flag[i] = filter.m_InputSignal_Flag;
				Input1.Signal_Freq[i] = filter.m_InputSignal_Freq;
			
				set_signal.m_Signal_Flag = Input1.Signal_Flag[i];
				set_signal.m_Signal_Freq = Input1.Signal_Freq[i];
				set_signal.Signal_Data();

				if(Input1.Signal_Flag[i] == "Sin"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sin_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "Cos"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Cos_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "Sinc"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.Sinc_Signal[t];
				}
				else if(Input1.Signal_Flag[i] == "White Noise"){
					for(int t=0; t<Total_Data; t++)
						Add_Signal[t] = set_signal.WhiteNoise_Signal[t];
				}

				for(int t=0; t<Total_Data; t++){
					Time_Signal1[t] += Add_Signal[t];
				}
				break;
			}
		}
		fourier_transform.Data_No = Total_Data;
		for(int x=0; x<Total_Data; x++)
			fourier_transform.Input_Signal[x] = Time_Signal1[x];
		fourier_transform.FT_Cal();
		for(int x=0; x<Total_Data; x++){
			Freq_Signal1[x] = fourier_transform.FT_Transform[x];
		}
	}
	Invalidate();
}

void CJungSangE_DSPView::OnDfInputreset()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for(int i=0; i<Signal_Box; i++){
		Input1.Signal_Flag[i] = "";
		Input1.Signal_Freq[i] = 1;
	}
	for(int i=0; i<Total_Data; i++){
		Add_Signal[i] = 0;
		Time_Signal1[i] = 0;
		Time_Signal3[i] = 0;
		Freq_Signal1[i] = 0;
		Freq_Signal3[i] = 0;
	}
	Invalidate();
}

void CJungSangE_DSPView::OnDfSetfilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	set_filter.m_SetFilter_Flag = m_DF_Filter_Flag;
	set_filter.m_SetFilter_Order = m_DF_Filter_Order;
	set_filter.m_SetFilter_CutOff = m_DF_Filter_CutOff;

	if(set_filter.DoModal() == IDOK){
		for(int i=0; i<Total_Data; i++){
			if(Time_Mode == "Digital Filter"){
				Time_Signal2[i] = 0;
				Time_Signal3[i] = 0;
				Freq_Signal2[i] = 0;
				Freq_Signal3[i] = 0;
			}else{
				Time_Signal1[i] = 0;
				Time_Signal2[i] = 0;
				Time_Signal3[i] = 0;
				Freq_Signal1[i] = 0;
				Freq_Signal2[i] = 0;
				Freq_Signal3[i] = 0;
			}
		}

		if(Time_Mode == "Digital Filter"){
		}else
			Time_Mode = "";
		Freq_Mode = "Digital Filter";
		m_DF_Filter_Flag = set_filter.m_SetFilter_Flag;
		m_DF_Filter_Order = set_filter.m_SetFilter_Order;
		m_DF_Filter_CutOff = set_filter.m_SetFilter_CutOff;
	}

	digital_filter.Data_No = Total_Data;
	digital_filter.m_Filter_Order = m_DF_Filter_Order;
	digital_filter.m_Filter_CutOff = m_DF_Filter_CutOff;

	if(m_DF_Filter_Flag == "Low Pass"){
		digital_filter.Digital_Filter_LowPass();
		for(int i=0; i<Total_Data; i++){
			Time_Signal2[i] = digital_filter.LowPass_TimeDomain[i];
			Freq_Signal2[i] = digital_filter.LowPass_Filter[i];
		}
	}
	else if(m_DF_Filter_Flag == "Butterworth"){
		digital_filter.Digital_Filter_Butterworth();
		for(int i=0; i<Total_Data; i++){
			Time_Signal2[i] = digital_filter.Butterworth_TimeDomain[i];
			Freq_Signal2[i] = digital_filter.Butterworth_Filter[i];
		}
	}
	else if(m_DF_Filter_Flag == "Chebyshev"){
		digital_filter.Digital_Filter_Chebyshev();
		for(int i=0; i<Total_Data; i++){
			Time_Signal2[i] = digital_filter.Chebyshev_TimeDomain[i];
			Freq_Signal2[i] = digital_filter.Chebyshev_Filter[i];
		}
	}
	Invalidate();
}

void CJungSangE_DSPView::OnDfFilterreset()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Freq_Mode = "";
	m_DF_Filter_Flag = "";
	m_DF_Filter_Order = 1;
	m_DF_Filter_CutOff = 1;

	for(int i=0; i<Total_Data; i++){
		Time_Signal2[i] = 0;
		Time_Signal3[i] = 0;
		Freq_Signal2[i] = 0;
		Freq_Signal3[i] = 0;
	}
	Invalidate();
}

void CJungSangE_DSPView::OnDfOutput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	convolution.m_Co_Data1=Total_Data;
	convolution.m_Co_Data2=Total_Data;

	for(int x=0; x<convolution.m_Co_Data1; x++)
		convolution.m_InData1[x]=Time_Signal1[x];

	for(int x=0; x<convolution.m_Co_Data2; x++)
		convolution.m_InData2[x]=Time_Signal2[x];

	convolution.ConVol();
	for(int x=0; x<Total_Data; x++)
		Time_Signal3[x]=convolution.m_OutData[x];

	for(int f=0; f<Total_Data; f++){
		Freq_Signal3[f] = Freq_Signal1[f] * Freq_Signal2[f];
	}
	Invalidate();
}

void CJungSangE_DSPView::OnAllreset()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	Time_Mode = Freq_Mode = "";
	
	for(int i=0; i<Signal_Box; i++){
		Input1.Signal_Flag[i] = "";
		Input1.Signal_Freq[i] = 1;
		Input2.Signal_Flag[i] = "";
		Input2.Signal_Freq[i] = 1;
	}
	for(int i=0; i<Total_Data; i++){
		Add_Signal[i] = 0;
		Time_Signal1[i] = 0;
		Time_Signal2[i] = 0;
		Time_Signal3[i] = 0;
		Freq_Signal1[i] = 0;
		Freq_Signal2[i] = 0;
		Freq_Signal3[i] = 0;
	}
	Invalidate();
}

void CJungSangE_DSPView::Display_Time_Signal(CDC* pDC)
{
	if(Time_Mode == "Convolution"){
		Text = "<컨볼루션> x(t) 입력";
		pDC->TextOut(TextTimeX,TextTimeY1,Text);
		Text = "<컨볼루션> h(t) 입력";
		pDC->TextOut(TextTimeX,TextTimeY2,Text);
		Text = "<컨볼루션> y(t) 출력";
		pDC->TextOut(TextTimeX,TextTimeY3,Text);
	}
	else if(Time_Mode == "Auto Correlation"){
		Text = "<자기상관> x(t) 입력";
		pDC->TextOut(TextTimeX,TextTimeY1,Text);
		Text = "<자기상관> x(t) 입력";
		pDC->TextOut(TextTimeX,TextTimeY2,Text);
		Text = "<자기상관> y(t) 출력";
		pDC->TextOut(TextTimeX,TextTimeY3,Text);
	}
	else if(Time_Mode == "Cross Correlation"){
		Text = "<상호상관> x1(t) 입력";
		pDC->TextOut(TextTimeX,TextTimeY1,Text);
		Text = "<상호상관> x2(t) 입력";
		pDC->TextOut(TextTimeX,TextTimeY2,Text);
		Text = "<상호상관> y(t) 출력";
		pDC->TextOut(TextTimeX,TextTimeY3,Text);
	}
	else if(Time_Mode == "Fourier Transform"){
		Text = "<푸리에 트랜스폼> x(t) 입력";
		pDC->TextOut(TextTimeX,TextTimeY1,Text);
		Text = "";
		pDC->TextOut(TextTimeX,TextTimeY2,Text);
		Text = "";
		pDC->TextOut(TextTimeX,TextTimeY3,Text);
	}
	else if(Time_Mode == "Digital Filter"){
		Text = "<디지털 필터> 시간축 상 입력 신호";
		pDC->TextOut(TextTimeX,TextTimeY1,Text);
		Text = "<디지털 필터> 시간축 상 필터";
		pDC->TextOut(TextTimeX,TextTimeY2,Text);
		Text = "<디지털 필터> 시간축 상 출력 신호";
		pDC->TextOut(TextTimeX,TextTimeY3,Text);

		Text = "<디지털 필터> 주파수 상 입력 신호";
		pDC->TextOut(TextFreqX,TextFreqY1,Text);
		Text = "<디지털 필터> 주파수 상 필터";
		pDC->TextOut(TextFreqX,TextFreqY2,Text);
		Text = "<디지털 필터> 주파수 상 출력 신호";
		pDC->TextOut(TextFreqX,TextFreqY3,Text);
	}

	adjmax.m_TotalData = draw_signal.Data_No =  Total_Data;

	for(int i=0; i<Total_Data; i++)
		adjmax.AdMax[i] = Time_Signal1[i];
	adjmax.Sort_Max();
	for(int i=0; i<Total_Data; i++)
		draw_signal.Display_Data[i] = adjmax.AdMax[i];
	draw_signal.Signal_View(pDC, TimeX, TimeY1);

	int x = TimeX+10, y = TimeY1_Start+10;
	for(int i=0; i<Signal_Box; i++){
		// 입력신호의 파형과 주파수를 화면에 표시한다.
		if(Input1.Signal_Flag[i]!=""){
			if(Input1.Signal_Flag[i] == "White Noise"){
				InputSignal.Format(_T("%s"),Input1.Signal_Flag[i]);
			}else{
				InputSignal.Format(_T("%s(%dHz)"),Input1.Signal_Flag[i], Input1.Signal_Freq[i]);
			}
			pDC->TextOut(x+(100*i),y,InputSignal);
		}
	}

	for(int i=0; i<Total_Data; i++)
		adjmax.AdMax[i] = Time_Signal2[i];
	adjmax.Sort_Max();
	for(int i=0; i<Total_Data; i++)
		draw_signal.Display_Data[i] = adjmax.AdMax[i];
	draw_signal.Signal_View(pDC, TimeX, TimeY2);

	x = TimeX+10, y = TimeY2_Start+10;
	for(int i=0; i<Signal_Box; i++){
		// 입력신호의 파형과 주파수를 화면에 표시한다.
		if(Input2.Signal_Flag[i]!=""){
			if(Input2.Signal_Flag[i] == "White Noise"){
				InputSignal.Format(_T("%s"), Input2.Signal_Flag[i]);
			}else{
				InputSignal.Format(_T("%s(%dHz)"),Input2.Signal_Flag[i], Input2.Signal_Freq[i]);
			}
			pDC->TextOut(x+(100*i),y,InputSignal);
		}
	}
	
	for(int i=0; i<Total_Data; i++)
		adjmax.AdMax[i] = Time_Signal3[i];
	adjmax.Sort_Max();
	for(int i=0; i<Total_Data; i++)
		draw_signal.Display_Data[i] = adjmax.AdMax[i];
	draw_signal.Signal_View(pDC, TimeX, TimeY3);
}

void CJungSangE_DSPView::Display_Freq_Signal(CDC* pDC)
{
	if(Freq_Mode == "Fourier Transform"){
		if((Time_Mode == "Convolution") || (Time_Mode == "Auto Correlation") || (Time_Mode == "Cross Correlation")){
			Text = "<주파수 변환> X(f)";
			pDC->TextOut(TextFreqX,TextFreqY1,Text);
			Text = "<주파수 변환> H(f)";
			pDC->TextOut(TextFreqX,TextFreqY2,Text);
			Text = "<주파수 변환> Y(f)";
			pDC->TextOut(TextFreqX,TextFreqY3,Text);
		}
		else if(Time_Mode == "Fourier Transform"){
			Text = "<주파수 변환> X(f)";
			pDC->TextOut(TextFreqX,TextFreqY1,Text);
			Text = "";
			pDC->TextOut(TextFreqX,TextFreqY2,Text);
			Text = "";
			pDC->TextOut(TextFreqX,TextFreqY3,Text);
		}
	}
	else if(Freq_Mode == "Digital Filter"){
		Text = "<디지털 필터> 시간축 상 입력 신호";
		pDC->TextOut(TextTimeX,TextTimeY1,Text);
		Text = "<디지털 필터> 시간축 상 필터";
		pDC->TextOut(TextTimeX,TextTimeY2,Text);
		Text = "<디지털 필터> 시간축 상 출력 신호";
		pDC->TextOut(TextTimeX,TextTimeY3,Text);

		Text = "<디지털 필터> 주파수 상 입력 신호";
		pDC->TextOut(TextFreqX,TextFreqY1,Text);
		Text = "<디지털 필터> 주파수 상 필터";
		pDC->TextOut(TextFreqX,TextFreqY2,Text);
		Text = "<디지털 필터> 주파수 상 출력 신호";
		pDC->TextOut(TextFreqX,TextFreqY3,Text);

		digital_filter.Digital_Filter_FilterValue(pDC);
	}

	adjmax.m_TotalData = draw_signal.Data_No = Total_Data;

	int wn1 = 0;
	int count1 = 0;
	for(int i=0; i<Signal_Box; i++){
		if(Input1.Signal_Flag[i] == "")
			break;
		else
			count1++;
		if(Input1.Signal_Flag[i] == "White Noise"){
			wn1++;
		}
	}

	for(int f=0; f<Total_Data; f++)
		adjmax.AdMax[f] = Freq_Signal1[f];
	adjmax.Sort_Max();
	for(int f=0; f<Total_Data; f++){
		draw_signal.Display_Data[f] = adjmax.AdMax[f];
		
		if(wn1 != count1){
			if(draw_signal.Display_Data[f] >= 0.5){
				int x = FreqX+f, y = FreqY1+10;
				double s = FreqY1-(draw_signal.Display_Data[f]*draw_signal.M)-20;
				// 해당 주파수와 크기를 화면에 표시한다.
				Hz.Format(_T("%dHz"),f);
				pDC->TextOut(x,y,Hz);
				Size.Format(_T("%0.2f"),draw_signal.Display_Data[f]);
				pDC->TextOutW(x,s,Size);
			}
		}
	}
	draw_signal.Signal_View(pDC, FreqX, FreqY1);

	int wn2 = 0;
	int count2 = 0;
	for(int i=0; i<Signal_Box; i++){
		if(Input2.Signal_Flag[i] == "")
			break;
		else
			count2++;
		if(Input2.Signal_Flag[i] == "White Noise"){
			wn2 = 1;
			break;
		}
	}

	for(int f=0; f<Total_Data; f++)
		adjmax.AdMax[f] = Freq_Signal2[f];
	adjmax.Sort_Max();
	for(int f=0; f<Total_Data; f++){
		draw_signal.Display_Data[f] = adjmax.AdMax[f];

		if((Time_Mode == "Convolution") || (Time_Mode == "Auto Correlation") || (Time_Mode == "Cross Correlation")){
			if(wn2 != count2){
				if(draw_signal.Display_Data[f] >= 0.5){
					int x = FreqX+f, y = FreqY2+10;
					double s = FreqY2-(draw_signal.Display_Data[f]*draw_signal.M)-20;
					// 해당 주파수와 크기를 화면에 표시한다.
					Hz.Format(_T("%dHz"),f);
					pDC->TextOut(x,y,Hz);
					Size.Format(_T("%0.2f"),draw_signal.Display_Data[f]);
					pDC->TextOutW(x,s,Size);
				}
			}
		}
	}
	draw_signal.Signal_View(pDC, FreqX, FreqY2);
	
	int ZFreq_OutputSignal = 0;
	for(int f=0; f<Total_Data; f++)
		adjmax.AdMax[f] = Freq_Signal3[f];
	adjmax.Sort_Max();

	for(int f=0; f<Total_Data; f++){
		draw_signal.Display_Data[f] = adjmax.AdMax[f];
		
		if(Freq_Mode == "Digital Filter"){
			if(wn1 != count1){
				if(f < m_DF_Filter_CutOff){
					if(draw_signal.Display_Data[f] > 0.707){
						int x = FreqX+f, y = FreqY3+10;
						double s = FreqY3-(draw_signal.Display_Data[f]*draw_signal.M)-20;
						// 해당 주파수와 크기를 화면에 표시한다.
						Hz.Format(_T("%dHz"),f);
						pDC->TextOut(x,y,Hz);
						Size.Format(_T("%0.2f"),draw_signal.Display_Data[f]);
						pDC->TextOutW(x,s,Size);
					}
				}else if(f >= m_DF_Filter_CutOff){
					if(draw_signal.Display_Data[f] > 0.05){
						int x = FreqX+f, y = FreqY3+10;
						double s = FreqY3-(draw_signal.Display_Data[f]*draw_signal.M)-20;
						// 해당 주파수와 크기를 화면에 표시한다.
						Hz.Format(_T("%dHz"),f);
						pDC->TextOut(x,y,Hz);
						Size.Format(_T("%0.2f"),draw_signal.Display_Data[f]);
						pDC->TextOutW(x,s,Size);
					}
				}
			}else if(wn1 == count1){
				// 해당 주파수의 주파수 상 출력신호의 크기가 0 이상일 때(근사값)
				if(draw_signal.Display_Data[f] >= 0.02){
					ZFreq_OutputSignal = 0;
					for(int i=(f+1); i<Total_Data; i++){
						if(draw_signal.Display_Data[i] < 0.02)
							ZFreq_OutputSignal +=1;
					}
					// 해당 주파수 이후의 모든 주파수의 크기가 0일 때(근사값)
					if(ZFreq_OutputSignal == Total_Data-(f+1)){
						int x = FreqX+f, y = FreqY3+10;
						// 해당 주파수를 표시한다.
						Hz.Format(_T("%dHz"),f);
						pDC->TextOut(x,y,Hz);
					}
				}// 이 구간은 white noise를 필터처리 했을 시 출력되는 가장 마지막 주파수를 표시한다.
			}
		}else{
			if(!((wn1 == count1)&&(wn2 == count2))){
				if(draw_signal.Display_Data[f] >= 0.5){
					int x = FreqX+f, y = FreqY3+10;
					double s = FreqY3-(draw_signal.Display_Data[f]*draw_signal.M)-20;
					// 해당 주파수와 크기를 화면에 표시한다.
					Hz.Format(_T("%dHz"),f);
					pDC->TextOut(x,y,Hz);
					Size.Format(_T("%0.2f"),draw_signal.Display_Data[f]);
					pDC->TextOutW(x,s,Size);
				}
			}
		}
	}
	draw_signal.Signal_View(pDC, FreqX, FreqY3);
}
