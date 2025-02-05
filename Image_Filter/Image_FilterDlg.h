
// Image_FilterDlg.h : header file
//

#pragma once
#include "CImg.h"
#include "afxwin.h"
#include "Filters.h"
#include <vector>
 
// CImageFilterDlg dialog
class CImageFilterDlg : public CDialog
{
// Construction
public:
	CImageFilterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGE_FILTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	cimg_library::CImg<unsigned char> applyFilters();
	cimg_library::CImg<unsigned char> image;
	CString imagePath;
	std::vector<Filters::Filter*> commandList;
	CString commandListText = _T("");
	CEdit CEdit1;
	CString edit1Text;
};
