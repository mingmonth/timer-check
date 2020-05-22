
// MFCTestStateCheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCTestStateCheck.h"
#include "MFCTestStateCheckDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable:4996)

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCTestStateCheckDlg dialog



CMFCTestStateCheckDlg::CMFCTestStateCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCTestStateCheckDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTestStateCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCTestStateCheckDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCTestStateCheckDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCTestStateCheckDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CMFCTestStateCheckDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CMFCTestStateCheckDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCTestStateCheckDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCTestStateCheckDlg::OnBnClickedButton4)
END_MESSAGE_MAP()

int g_recvCount = 0;

unsigned __int64 g_Timer = 0l;

void CALLBACK onReceiveTest(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime) {
	g_Timer = GetTickCount64();
	g_recvCount++;
	printf("g_recvCount: %d\n", g_recvCount);
}

int g_checkCount = 0;

void CALLBACK checkRecv(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime) {
	unsigned __int64 curTicCount = GetTickCount64();
	
	//printf("%I64u\n", curTicCount - g_Timer);	
	printf("g_checkCount: %d\n", g_checkCount);
	
	if (curTicCount - g_Timer > 1500) {
		g_checkCount++;
		if (g_checkCount > 2) {
			printf("recv timer is died.\n");
			g_checkCount = 2;			
		}
	}
	else {
		if (g_checkCount == 0) {
			printf("recv timer is alive.\n");
		}
		else {
			g_checkCount--;
		}
	}	
}

HHOOK hHook{ NULL };

void init() {
	AllocConsole();
	freopen("CONOUT$", "wt", stdout);
}

void close() {
	FreeConsole();
	UnhookWindowsHookEx(hHook);
	//EndDialog(hDlg, LOWORD(wParam));
}

// CMFCTestStateCheckDlg message handlers

BOOL CMFCTestStateCheckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	init();
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

void CMFCTestStateCheckDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCTestStateCheckDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCTestStateCheckDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTestStateCheckDlg::OnBnClickedButton1()	// Start
{
	// TODO: Add your control notification handler code here
	// 타이머 생성
	SetTimer(1, 1000, onReceiveTest);
	SetTimer(2, 1000, checkRecv);
}


void CMFCTestStateCheckDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	KillTimer(2);
}


void CMFCTestStateCheckDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	close();
	CDialogEx::OnCancel();
}


void CMFCTestStateCheckDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	close();
	CDialogEx::OnOK();
}


void CMFCTestStateCheckDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	SetTimer(1, 1000, onReceiveTest);
}


void CMFCTestStateCheckDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
}
