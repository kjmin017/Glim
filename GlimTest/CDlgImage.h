#pragma once
#include "afxdialogex.h"


// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CImage m_image;
	CWnd* m_pParent;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void drawCircleThroughThreePoints(unsigned char* fm);
	void drawCircleThroughThreePoints(unsigned char* fm, CPoint p1, CPoint p2, CPoint p3, int nThickness);
	void drawCircleWithThickness(unsigned char* fm, int x, int y, int nRadius, int nThickness, int nGray);
	void InitImage();
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void getCircleCenterAndRadius(CPoint p1, CPoint p2, CPoint p3, CPoint& center, int& radius);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
