
// GlimTestDlg.h: 헤더 파일
//
#include "CDlgimage.h"
#pragma once


// CGlimTestDlg 대화 상자
class CGlimTestDlg : public CDialogEx
{

// 생성입니다.
public:
	CPoint m_clickPoints[3];
	int m_clickCount = 0;

	
	int m_circleRadius;
	int m_draggingPointIndex = -1;
	
	bool m_drawCircles;
	CGlimTestDlg(CWnd* pParent = nullptr)
		: CDialogEx(IDD_GLIMTEST_DIALOG, pParent)
		, m_circleThickness(2)
		, m_radius(10)
	{
		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}	// 표준 생성자입니다.

	CDlgImage* m_pDlgImage;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnEnChangeEditEdge();
	afx_msg void OnBnClickedButtonRandom();
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);
public:
	afx_msg void OnBnClickedButtonDialog();
	afx_msg void OnDestroy();

//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int m_circleThickness;
	int m_radius;
	afx_msg void OnEnChangeEditRad();
	afx_msg void OnBnClickedButtonRad();
	afx_msg void OnBnClickedButtonEdge();
	CEdit mEdge;
	CEdit mRad;
};
