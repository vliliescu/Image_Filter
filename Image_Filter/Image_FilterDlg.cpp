// Image_FilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Image_Filter.h"
#include "Image_FilterDlg.h"
#include "afxdialogex.h"
#include "CImg.h"
#include "Filters.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageFilterDlg dialog



CImageFilterDlg::CImageFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_IMAGE_FILTER_DIALOG, pParent)
	, edit1Text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, CEdit1);
	DDX_Text(pDX, IDC_EDIT1, edit1Text);
}

BEGIN_MESSAGE_MAP(CImageFilterDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CImageFilterDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CImageFilterDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CImageFilterDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CImageFilterDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CImageFilterDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &CImageFilterDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CImageFilterDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON6, &CImageFilterDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CImageFilterDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CImageFilterDlg message handlers

BOOL CImageFilterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageFilterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageFilterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageFilterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

cimg_library::CImg<unsigned char> CImageFilterDlg::applyFilters()
{
	cimg_library::CImg<unsigned char> temp = image;
	for (std::vector<Filters::Filter*>::iterator it = commandList.begin(); it != commandList.end(); ++it)
	{
		(*it)->setImage(temp);
		temp = (*it)->applyFilter();
	}
	temp.save("output.bmp");
	return temp;
}

void CImageFilterDlg::OnBnClickedButton4()
{
	CFileDialog fileDialog(true, NULL, NULL, OFN_FILEMUSTEXIST, _T("Bitmap Files(*.bmp)|*.bmp|JPEG Files(*.jpg,*.jpeg)|*.jpg;*.jpeg|PNG Files(*.png)|*.png||"));
	fileDialog.DoModal();
	imagePath = fileDialog.GetPathName();
	try {
		image = cimg_library::CImg<unsigned char>(CT2A(imagePath));
		cimg_library::CImgDisplay main_disp(image, "The following image was loaded");
		while (!main_disp.is_closed())
			main_disp.wait();
		edit1Text = "Your image has been loaded\r\nPlease select filters.";
		UpdateData(false);
	}
	catch (cimg_library::CImgIOException e) {
		edit1Text = "Your image has failed to load\r\nPlease try again.";
		UpdateData(false);
	}
}

void CImageFilterDlg::OnBnClickedButton1()
{
	Filters::EdgeDetectionFilter* g = new Filters::EdgeDetectionFilter();
	commandList.push_back(g);
	commandListText += _T("Edge;");
	edit1Text = _T("Filters entered so far:\r\n") + commandListText;
	UpdateData(false);
}

void CImageFilterDlg::OnBnClickedButton2()
{
	Filters::GaussianFilter* g = new Filters::GaussianFilter();
	commandList.push_back(g);
	commandListText += _T("Gaussian;");
	edit1Text = _T("Filters entered so far:\r\n") + commandListText;
	UpdateData(false);
}


void CImageFilterDlg::OnBnClickedButton3()
{
	Filters::SharpenFilter* g = new Filters::SharpenFilter();
	commandList.push_back(g);
	commandListText += _T("Sharpen;");
	edit1Text = _T("Filters entered so far:\r\n") + commandListText;
	UpdateData(false);
}


void CImageFilterDlg::OnBnClickedButton5()
{
	if (image._data == NULL)
		MessageBox(_T("Please enter an image first"));
	else
	{
		cimg_library::CImgDisplay main_disp(applyFilters(), "The resulting image is the following:");
		while (!main_disp.is_closed())
			main_disp.wait();
		edit1Text = "The filters have been successfully\r\napplied";
		UpdateData(false);
	}
}


void CImageFilterDlg::OnBnClickedButton8()
{
	image = cimg_library::CImg<unsigned char>();
	imagePath = "";
	edit1Text = "Image has been cleared";
	UpdateData(false);
}


void CImageFilterDlg::OnBnClickedButton9()
{
	commandList.clear();
	commandListText = "";
	edit1Text = "Filter list has been cleared";
	UpdateData(false);
}


void CImageFilterDlg::OnBnClickedButton6()
{
	if (image._data == NULL)
	{
		MessageBox(_T("Please enter an image first"));
	}
	else
	{
		std::ofstream file("output.txt");
		file << (CT2A)imagePath << "\n" << (CT2A)commandListText;
	}
}


void CImageFilterDlg::OnBnClickedButton7()
{
	bool loadImage = false;
	cimg_library::CImg<unsigned int> backup_image = image;
	std::ifstream file("output.txt", std::ifstream::in);
	char buf[255];
	file.getline(buf, (std::streamsize)255);

	try{
		image = cimg_library::CImg<unsigned char>(buf);
		imagePath = CA2T(buf);
		loadImage = true;
	}
	catch (cimg_library::CImgIOException e) {
		edit1Text = "Your image has failed to load\r\nPlease try again.";
		UpdateData(false);
		image = backup_image;
	}
	
	file.getline(buf, (std::streamsize)255);
	commandListText = "";
	commandList.clear();
	int pos = 0;
	CString commandsFromFile = CA2T(buf);
	CString token = commandsFromFile.Tokenize(_T(";"), pos);
	while (!token.IsEmpty())
	{
		if (token == "Edge")
		{
			Filters::EdgeDetectionFilter* g = new Filters::EdgeDetectionFilter();
			commandList.push_back(g);
			commandListText += token + _T(";");
		}
		else if (token == "Sharpen")
		{
			Filters::SharpenFilter* g = new Filters::SharpenFilter();
			commandList.push_back(g);
			commandListText += token + _T(";");
		}
		else if (token == "Gaussian")
		{
			Filters::GaussianFilter* g = new Filters::GaussianFilter();
			commandList.push_back(g);
			commandListText += token + _T(";");
		}
		token = commandsFromFile.Tokenize(_T(";"), pos);
	}

	if (image._data == NULL)
	{
		edit1Text = _T("Image load failed \r\nPlease load an image \r\nBefore applying filters");
		UpdateData(false);
	}
	else
	{
		if (loadImage == false)
			edit1Text = _T("Image load failed \r\nPrevious image was kept\r\nFilters: ") + commandListText;
		else
			edit1Text = _T("Image and filters loaded:\r\n") + commandListText;
		UpdateData(false);
		cimg_library::CImgDisplay main_disp(applyFilters(), "The resulting image is the following:");
		while (!main_disp.is_closed())
			main_disp.wait();
	}
}
