================================================================================
    MFC 라이브러리 : DSP 프로젝트 개요
================================================================================

응용 프로그램 마법사에서 DSP 응용 프로그램을 
만들었습니다. 이 응용 프로그램은 MFC의 기본 사용법을 보여 줄 뿐만 아니라 응용 
프로그램작성을 위한 기본 구조를 제공합니다.

/////////////////////////////////////////////////////////////////////////////

주 프레임 창의 경우:
    프로젝트에는 표준 MFC 인터페이스가 포함됩니다.

MainFrm.h, MainFrm.cpp
    이 파일에는 프레임 클래스 CMainFrame이(가) 들어 있습니다.
    이 클래스는CFrameWnd에서 파생되며 모든 SDI 프레임 기능을 제어합니다.

/////////////////////////////////////////////////////////////////////////////

기타 기능:

ActiveX 컨트롤
    응용 프로그램에서 ActiveX 컨트롤을 사용할 수 있도록 지원합니다.

인쇄 및 인쇄 미리 보기 지원
    응용 프로그램 마법사가 MFC 라이브러리에서 CView 클래스의 멤버 함수를 호출하여 인쇄, 인쇄 설정
    및 인쇄 미리 보기 명령을 처리하는 코드를 생성했습니다.

/////////////////////////////////////////////////////////////////////////////

기타 표준 파일:

StdAfx.h, StdAfx.cpp
    이 파일은 미리 컴파일된 헤더 파일(PCH)인 JungSangE_DSP.pch와
    미리 컴파일된 형식 파일인 StdAfx.obj를 빌드하는 데 사용됩니다.

Resource.h
    새 리소스 ID를 정의하는 표준 헤더 파일입니다.
    Microsoft Visual C++에서 이 파일을 읽고 업데이트합니다.

/////////////////////////////////////////////////////////////////////////////
