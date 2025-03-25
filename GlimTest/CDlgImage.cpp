// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "GlimTest.h"
#include "GlimTestDlg.h"
#include "afxdialogex.h"
#include "CDlgImage.h"
#include <thread>
#include <vector>
// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{

	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기
void CDlgImage::InitImage()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;
	if (m_image) {
		m_image.Destroy();
	}
	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CDialogEx::OnInitDialog();
	SetWindowText(_T("Origin Image"));
	MoveWindow(0, 0, 640, 480);
	InitImage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image)
		m_image.Draw(dc, 0, 0);

	
}



void CDlgImage::OnLButtonDown(UINT nFlags, CPoint point)
{
	CGlimTestDlg* pParentDlg = (CGlimTestDlg*)GetParent();

	
	for (int i = 0; i < 3; i++) {
		CPoint p = pParentDlg->m_clickPoints[i];
		if (abs(p.x - point.x) < 10 && abs(p.y - point.y) < 10) { 
			pParentDlg->m_draggingPointIndex = i;
			break;
		}
	}

	if (pParentDlg->m_draggingPointIndex == -1) {
		if (pParentDlg->m_clickCount < 3) {
			CString str;
			pParentDlg->m_clickPoints[pParentDlg->m_clickCount] = point;
			
			str.Format(_T("X: %d, Y: %d"), point.x, point.y);
			switch (pParentDlg->m_clickCount)
			{
				//case 1: SetDlgItemText(IDC_STATIC_COORD1, str); break;
				//case 2: SetDlgItemText(IDC_STATIC_COORD2, str); break;
				//case 3: SetDlgItemText(IDC_STATIC_COORD3, str); break;
			}
			int nRadius = pParentDlg->m_radius;
			int nblack = 0;
			int nWidth = m_image.GetWidth();
			int nHeight = m_image.GetHeight();
			int nPitch = m_image.GetPitch();
			unsigned char* fm = (unsigned char*)m_image.GetBits();


			drawCircle(fm, point.x, point.y, nRadius, nblack);

			pParentDlg->m_clickCount++;
		if(pParentDlg->m_clickCount == 3) {
			drawCircleThroughThreePoints(fm);
		}
			Invalidate();
		}
		
	}

	CDialogEx::OnLButtonDown(nFlags, point);
	
}

void CDlgImage::OnLButtonUp(UINT nFlags, CPoint point)
{
	CGlimTestDlg* pParentDlg = (CGlimTestDlg*)GetParent();
	pParentDlg->m_draggingPointIndex = -1;

	CDialogEx::OnLButtonUp(nFlags, point);
}
void CDlgImage::OnMouseMove(UINT nFlags, CPoint point)
{
	CGlimTestDlg* pParentDlg = (CGlimTestDlg*)GetParent(); 
	if (pParentDlg->m_draggingPointIndex != -1) {
		

		
		pParentDlg->m_clickPoints[pParentDlg->m_draggingPointIndex] = point;
		InitImage();
		for (int i = 0; i < 3; i++) {
			CPoint p = pParentDlg->m_clickPoints[i];
			int nRadius = pParentDlg->m_radius;
			int nblack = 0;
			int nWidth = m_image.GetWidth();
			int nHeight = m_image.GetHeight();
			int nPitch = m_image.GetPitch();
			unsigned char* fm = (unsigned char*)m_image.GetBits();
			drawCircle(fm, p.x, p.y, nRadius, nblack);
		}
		
		unsigned char* fm = (unsigned char*)m_image.GetBits();
		drawCircleThroughThreePoints(fm);

		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
void CDlgImage::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x;
	int nCenterY = y;
	int nPitch = m_image.GetPitch();

	for (int j = y - nRadius; j <= y + nRadius; j++) {
		for (int i = x - nRadius; i <= x + nRadius; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius)) {
				if (i >= 0 && i < m_image.GetWidth() && j >= 0 && j < m_image.GetHeight()) {
					fm[j * nPitch + i] = nGray;
				}
			}
		}
	}
}
bool CDlgImage::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist <= nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}

void CDlgImage::getCircleCenterAndRadius(CPoint p1, CPoint p2, CPoint p3, CPoint& center, int& radius)
{
	

	double x1 = p1.x, y1 = p1.y;
	double x2 = p2.x, y2 = p2.y;
	double x3 = p3.x, y3 = p3.y;

	double d = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

	double ux = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / d;
	double uy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / d;

	
	center = CPoint((int)ux, (int)uy);

	
	radius = (int)sqrt(pow(x1 - ux, 2) + pow(y1 - uy, 2));
}
#include <iostream>
void CDlgImage::drawCircleThroughThreePoints(unsigned char* fm)
{
	CGlimTestDlg* pParentDlg = (CGlimTestDlg*)GetParent();

	CPoint p1 = pParentDlg->m_clickPoints[0];
	CPoint p2 = pParentDlg->m_clickPoints[1];
	CPoint p3 = pParentDlg->m_clickPoints[2];

	std::cout << "p1: " << p1.x << ", " << p1.y << std::endl;
	std::cout << "p2: " << p2.x << ", " << p2.y << std::endl;
	std::cout << "p3: " << p3.x << ", " << p3.y << std::endl;
	CPoint center;
	int radius;
	getCircleCenterAndRadius(p1, p2, p3, center, radius);

	
	int nThickness = pParentDlg->m_circleThickness;

	
	int nBlack = 0;  
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	
	drawCircleWithThickness(fm, center.x, center.y, radius, nThickness, nBlack);

	
	Invalidate();
}
void CDlgImage::drawCircleThroughThreePoints(unsigned char* fm, CPoint p1, CPoint p2, CPoint p3, int nThickness)
{
	CGlimTestDlg* pParentDlg = (CGlimTestDlg*)GetParent();

	std::cout << "p1: " << p1.x << ", " << p1.y << std::endl;
	std::cout << "p2: " << p2.x << ", " << p2.y << std::endl;
	std::cout << "p3: " << p3.x << ", " << p3.y << std::endl;
	CPoint center;
	int radius;
	getCircleCenterAndRadius(p1, p2, p3, center, radius);



	int nBlack = 0;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();


	drawCircleWithThickness(fm, center.x, center.y, radius, nThickness, nBlack);


	Invalidate();
}

void CDlgImage::drawCircleWithThickness(unsigned char* fm, int x, int y, int nRadius, int nThickness, int nGray)
{
	int nPitch = m_image.GetPitch();
	int outerRadius = nRadius;
	int innerRadius = nRadius - nThickness;

	
	int numThreads = std::thread::hardware_concurrency();
	if (numThreads == 0) numThreads = 4; 

	
	std::vector<std::thread> threads;
	int step = (outerRadius * 2) / numThreads;

	for (int t = 0; t < numThreads; t++) {
		int startY = y - outerRadius + t * step;
		int endY = (t == numThreads - 1) ? (y + outerRadius) : (startY + step);

		threads.push_back(std::thread([=]() {
			for (int j = startY; j < endY; j++) {
				for (int i = x - outerRadius; i <= x + outerRadius; i++) {
					if (isInCircle(i, j, x, y, outerRadius) && !isInCircle(i, j, x, y, innerRadius)) {
						if (j >= 0 && j < m_image.GetHeight() && i >= 0 && i < m_image.GetWidth()) {
							fm[j * nPitch + i] = nGray;
						}
					}
				}
			}
			}));
	}

	// 모든 쓰레드가 끝날 때까지 대기
	for (auto& th : threads) {
		th.join();
	}

	// 화면 갱신은 UI 스레드에서 실행
	Invalidate();
}


//{
//	int nCenterX = x;
//	int nCenterY = y;
//	int nPitch = m_image.GetPitch();
//
//
//	int outerRadius = nRadius;
//	int innerRadius = nRadius - nThickness;
//
//
//	for (int j = y - outerRadius; j <= y + outerRadius; j++) {
//		for (int i = x - outerRadius; i <= x + outerRadius; i++) {
//			if (isInCircle(i, j, nCenterX, nCenterY, outerRadius) && !isInCircle(i, j, nCenterX, nCenterY, innerRadius)) {
//				if (j >= 0 && j < m_image.GetHeight() && i >= 0 && i < m_image.GetWidth()) {
//					fm[j * nPitch + i] = nGray;
//				}
//			}
//		}
//	}
//}
