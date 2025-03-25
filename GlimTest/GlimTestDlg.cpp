
// GlimTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GlimTest.h"
#include "GlimTestDlg.h"
#include "CDlgImage.h"
#include "afxdialogex.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_LBUTTONDOWN()
//ON_WM_LBUTTONDOWN()
//ON_WM_LBUTTONDBLCLK()
//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CGlimTestDlg 대화 상자



void CGlimTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_EDGE, edge);
	//  DDX_Text(pDX, IDC_EDIT_EDGE, m_circleThickness);
	DDX_Text(pDX, IDC_EDIT_RAD, m_radius);
	DDX_Control(pDX, IDC_EDIT_EDGE, mEdge);
	DDX_Control(pDX, IDC_EDIT_RAD, mRad);
}

BEGIN_MESSAGE_MAP(CGlimTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CGlimTestDlg::OnBnClickedButtonClear)
	ON_EN_CHANGE(IDC_EDIT_EDGE, &CGlimTestDlg::OnEnChangeEditEdge)
	ON_BN_CLICKED(IDC_BUTTON_RANDOM, &CGlimTestDlg::OnBnClickedButtonRandom)
	ON_BN_CLICKED(IDC_BUTTON_DIALOG, &CGlimTestDlg::OnBnClickedButtonDialog)
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
	ON_EN_CHANGE(IDC_EDIT_RAD, &CGlimTestDlg::OnEnChangeEditRad)
	ON_BN_CLICKED(IDC_BUTTON_RAD, &CGlimTestDlg::OnBnClickedButtonRad)
	ON_BN_CLICKED(IDC_BUTTON_EDGE, &CGlimTestDlg::OnBnClickedButtonEdge)
	END_MESSAGE_MAP()


// CGlimTestDlg 메시지 처리기

BOOL CGlimTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//MoveWindow(0, 0, 1280, 800);
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);


	m_clickCount = 0;
	m_drawCircles = true;
	m_radius = 10;
	m_circleThickness = 2;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGlimTestDlg::OnBnClickedButtonClear()
{
	m_clickCount = 0;
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	memset(fm, 0xff, nWidth * nHeight);
	
	m_pDlgImage->Invalidate(); // 다시 그리기 요청
	m_circleThickness = 2;
	m_radius = 10;
	UpdateData(false);
	
}

void CGlimTestDlg::OnEnChangeEditEdge()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// ENM_CHANGE가 있으면 마스크에 ORed를 플래그합니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void DrawRandomCircles(CDlgImage* pDlgImage, CGlimTestDlg* pDlg)
{

	int nWidth = pDlgImage->m_image.GetWidth();
	int nHeight = pDlgImage->m_image.GetHeight();
	int nRadius = pDlg->m_radius;
	int nBlack = 0;
	int nPitch = pDlgImage->m_image.GetPitch();
	unsigned char* fm = (unsigned char*)pDlgImage->m_image.GetBits();

	for (int j = 0; j < 10; j++) {
		pDlgImage->InitImage();
		for (int i = 0; i < 3; i++) {
			pDlg->m_clickPoints[i] = CPoint(rand() % nWidth, rand() % nHeight);
			pDlgImage->drawCircle(fm, pDlg->m_clickPoints[i].x, pDlg->m_clickPoints[i].y, nRadius, nBlack);
		}
		unsigned char* fm = (unsigned char*)pDlgImage->m_image.GetBits();
		pDlgImage->drawCircleThroughThreePoints(fm, pDlg->m_clickPoints[0], pDlg->m_clickPoints[1], pDlg->m_clickPoints[2], pDlg->m_circleThickness);
		pDlgImage->Invalidate();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void CGlimTestDlg::OnBnClickedButtonRandom()
{
	std::thread drawThread([this]() {
		DrawRandomCircles(m_pDlgImage, this);
		});

	drawThread.detach();
}
bool CGlimTestDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}

void CGlimTestDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x;
	int nCenterY = y;
	int nPitch = m_pDlgImage->m_image.GetPitch();


	for (int j = y-nRadius; j < y + nRadius; j++) {
		for (int i = x-nRadius; i < x + nRadius * 2; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius) && i>=0 && j>=0)
				fm[j * nPitch + i] = nGray;
		}
	}
}

//void CGlimTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	
//	CGlimTestDlg::OnLButtonDown(nFlags, point);
//}

void CGlimTestDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pDlgImage->Invalidate();
	CDialogEx::OnLButtonUp(nFlags, point);
}



void CGlimTestDlg::OnBnClickedButtonDialog()
{
	m_pDlgImage->ShowWindow(SW_SHOW);
	
}

void CGlimTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete m_pDlgImage;
}


void CGlimTestDlg::OnEnChangeEditRad()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// ENM_CHANGE가 있으면 마스크에 ORed를 플래그합니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CGlimTestDlg::OnBnClickedButtonRad()
{
	CString str;
	mRad.GetWindowTextW(str);
	MessageBox(str);
	m_radius = _ttoi(str);	
}

void CGlimTestDlg::OnBnClickedButtonEdge()
{
	CString str;
	mEdge.GetWindowTextW(str);
	MessageBox(str);
	m_circleThickness = _ttoi(str);
}
