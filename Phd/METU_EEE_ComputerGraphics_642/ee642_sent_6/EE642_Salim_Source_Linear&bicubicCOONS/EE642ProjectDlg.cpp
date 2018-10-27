// EE642ProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EE642Project.h"
#include "EE642ProjectDlg.h"
#include "UserContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEE642ProjectDlg dialog

CEE642ProjectDlg::CEE642ProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEE642ProjectDlg::IDD, pParent)
	, m_input1Value(0)
	, m_input2Value(0)
{
	//{{AFX_DATA_INIT(CEE642ProjectDlg)
	m_radioSelection = -1;
	m_edit3Value = 0.0;
	m_edit4Value = 0.0;
	m_edit5Value = 0.0;
	m_input6Value = 0.0;
	m_input7Value = 0.0;
	m_input8Value = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_userContext=(CMainContext2::GetInstance());
}

void CEE642ProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEE642ProjectDlg)
	DDX_Control(pDX, IDC_STATUS_AREA, m_statusAreaWnd);
	DDX_Control(pDX, IDC_EDIT8, m_input8Edit);
	DDX_Control(pDX, IDC_EDIT7, m_input7Edit);
	DDX_Control(pDX, IDC_EDIT6, m_input6Edit);
	DDX_Control(pDX, IDC_STATIC6, m_input6Name);
	DDX_Control(pDX, IDC_STATIC5, m_input5Name);
	DDX_Control(pDX, IDC_STATIC4, m_input4Name);
	DDX_Control(pDX, IDC_STATIC3, m_input3Name);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_menuTitleBar);
	DDX_Control(pDX, IDC_EDIT9, m_gridInfo);
	DDX_Control(pDX, IDC_INFO_AREA, m_infoArea);
	DDX_Control(pDX, IDC_STATIC_Y, m_statY);
	DDX_Control(pDX, IDC_STATIC_X, m_statX);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_RADIO1, m_radioBtn);
	DDX_Control(pDX, IDC_RENDER_AREA, m_renderArea);
	DDX_Radio(pDX, IDC_RADIO1, m_radioSelection);
	DDX_Text(pDX, IDC_EDIT3, m_edit3Value);
	DDX_Text(pDX, IDC_EDIT4, m_edit4Value);
	DDX_Text(pDX, IDC_EDIT5, m_edit5Value);
	DDX_Text(pDX, IDC_EDIT6, m_input6Value);
	DDX_Text(pDX, IDC_EDIT7, m_input7Value);
	DDX_Text(pDX, IDC_EDIT8, m_input8Value);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MENU_AREA, m_menuArea);
	DDX_Control(pDX, IDC_BUTTON1, m_menuButtons[0]);
	DDX_Control(pDX, IDC_BUTTON2, m_menuButtons[1]);
	DDX_Control(pDX, IDC_BUTTON3, m_menuButtons[2]);
	DDX_Control(pDX, IDC_BUTTON4, m_menuButtons[3]);
	DDX_Control(pDX, IDC_BUTTON5, m_menuButtons[4]);
	DDX_Control(pDX, IDC_BUTTON6, m_menuButtons[5]);
	DDX_Control(pDX, IDC_BUTTON7, m_menuButtons[6]);
	DDX_Control(pDX, IDC_BUTTON8, m_menuButtons[7]);
	DDX_Control(pDX, IDC_BUTTON9, m_menuButtons[8]);
	DDX_Control(pDX, IDC_STATIC1, m_input1Name);
	DDX_Control(pDX, IDC_STATIC2, m_input2Name);
	DDX_Control(pDX, IDC_EDIT1, m_input1Edit);
	DDX_Control(pDX, IDC_EDIT2, m_input2Edit);
	DDX_Text(pDX, IDC_EDIT1, m_input1Value);
	DDX_Text(pDX, IDC_EDIT2, m_input2Value);
	DDX_Control(pDX, IDC_BUTTON_APPLY, m_applyButton);
}

BEGIN_MESSAGE_MAP(CEE642ProjectDlg, CDialog)
	//{{AFX_MSG_MAP(CEE642ProjectDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_BUTTON_CLS, OnButtonCls)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnBnClickedButtonApply)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEE642ProjectDlg message handlers

BOOL CEE642ProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	ChangeContext(m_userContext);
	m_userContext->SetManager(this);
	m_renderArea.SetManager(this);

	m_gridInfo.SetWindowText("Grid Size: 50 pixels \r\nWidth: 600 pixels \r\nHeight: 600 pixels");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEE642ProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEE642ProjectDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEE642ProjectDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEE642ProjectDlg::SetCurrentGraphObject(CCompGraphObject* obj, bool clearPrevious)
{
	C642Manager::SetCurrentGraphObject(obj, clearPrevious);
	m_renderArea.RedrawWindow();
}

void CEE642ProjectDlg::OnBnClickedButton1()
{
	m_userContext->Menu1Selected();
}

void CEE642ProjectDlg::OnBnClickedButton2()
{
	m_userContext->Menu2Selected();
}

void CEE642ProjectDlg::OnBnClickedButton3()
{
	m_userContext->Menu3Selected();
}

void CEE642ProjectDlg::OnBnClickedButton4()
{
	m_userContext->Menu4Selected();
}

void CEE642ProjectDlg::OnBnClickedButton5()
{
	m_userContext->Menu5Selected();
}

int CEE642ProjectDlg::GetRadioSel()
{
	UpdateData();
	return m_radioSelection;
}
void CEE642ProjectDlg::SetRadioSel(int sel)
{
	m_radioSelection = sel;
	UpdateData(FALSE);
}

double CEE642ProjectDlg::GetLineParamA()
{
	UpdateData();
	return m_edit3Value;
}
double CEE642ProjectDlg::GetLineParamB()
{
	UpdateData();
	return m_edit4Value;
}

void CEE642ProjectDlg::ChangeContext(CUserContext* newContext)
{
	C642Manager::ChangeContext(newContext);
	for (int i=0; i<m_userContext->GetMenuCount(); i++)
	{
		m_menuButtons[i].ShowWindow(SW_SHOW);
		m_menuButtons[i].SetWindowText(m_userContext->GetMenuItemText(i));
	}
	for (; i<MAX_MENU_COUNT; i++)
	{
		m_menuButtons[i].ShowWindow(SW_HIDE);
	}
	m_menuTitleBar.SetWindowText(m_userContext->GetContextName());
	SetInfoAreaText(m_userContext->GetContextInfo());
	ClearInputArea();
}

void CEE642ProjectDlg::DrawLine(CPoint p1, CPoint p2)
{
	CDC* pDC = m_renderArea.GetDC();
	CRect clientRect;
	m_renderArea.GetClientRect(clientRect);
	int xOrg = clientRect.Width()/2;
	int yOrg = clientRect.Height()/2;
	pDC->SetViewportExt(clientRect.Size());
	pDC->SetViewportOrg(xOrg, yOrg);
	pDC->SetBkMode(TRANSPARENT);
	CPen p;
	p.CreatePen(PS_DOT, 1, 0xffff);
	CPen* oldP = pDC->SelectObject(&p);
	pDC->MoveTo(p1.x, -p1.y);
	pDC->LineTo(p2.x, -p2.y);
	pDC->SelectObject(oldP);
	ReleaseDC(pDC);
}

void CEE642ProjectDlg::SetInfoAreaText(CString str)
{
	m_infoArea.SetWindowText(str);
}

void CEE642ProjectDlg::SetMenuTitle(CString str)
{
	m_menuTitleBar.SetWindowText(str);
}

void CEE642ProjectDlg::ClearInputArea(void)
{
	m_input1Edit.ShowWindow(SW_HIDE);
	m_input2Edit.ShowWindow(SW_HIDE);
	m_input1Name.ShowWindow(SW_HIDE);
	m_input2Name.ShowWindow(SW_HIDE);
	m_input1Value = 0;
	m_input2Value = 0;
	m_applyButton.ShowWindow(SW_HIDE);
	m_edit5.ShowWindow(SW_HIDE);
	m_input3Name.ShowWindow(SW_HIDE);
	m_edit5Value = 0;

	m_input6Edit.ShowWindow(SW_HIDE);
	m_input4Name.ShowWindow(SW_HIDE);
	m_input6Value = 0;

	m_input7Edit.ShowWindow(SW_HIDE);
	m_input5Name.ShowWindow(SW_HIDE);
	m_input7Value = 0;
	m_input8Edit.ShowWindow(SW_HIDE);
	m_input6Name.ShowWindow(SW_HIDE);
	m_input8Value = 0;
}

void CEE642ProjectDlg::LineParametersShow(int cmd)
{
	m_edit3.ShowWindow(cmd);
	m_edit4.ShowWindow(cmd);
	m_statX.ShowWindow(cmd);
	m_statY.ShowWindow(cmd);
}

void CEE642ProjectDlg::SetInput1Name(CString name)
{
	m_input1Name.SetWindowText(name);
	m_input1Value = 0;
	m_input1Edit.SetWindowText("0");
//	UpdateData(FALSE);
	m_input1Name.ShowWindow(SW_SHOW);
	m_input1Edit.ShowWindow(SW_SHOW);
	m_applyButton.ShowWindow(SW_SHOW);
	m_input1Edit.SetFocus();
}

void CEE642ProjectDlg::SetInput2Name(CString name)
{
	m_input2Name.SetWindowText(name);
	m_input2Value = 0;
	m_input2Edit.SetWindowText("0");
//	UpdateData(FALSE);
	m_input2Name.ShowWindow(SW_SHOW);
	m_input2Edit.ShowWindow(SW_SHOW);
	m_applyButton.ShowWindow(SW_SHOW);
}
void CEE642ProjectDlg::SetInput3Name(CString name)
{
	m_input3Name.SetWindowText(name);
	m_edit5Value = 0;
//	UpdateData(FALSE);
	m_input3Name.ShowWindow(SW_SHOW);
	m_edit5.SetWindowText("0");
	m_edit5.ShowWindow(SW_SHOW);
	m_applyButton.ShowWindow(SW_SHOW);
}
void CEE642ProjectDlg::SetInput4Name(CString name)
{
	m_input4Name.SetWindowText(name);
	m_input6Value = 0;
//	UpdateData(FALSE);
	m_input4Name.ShowWindow(SW_SHOW);
	m_input6Edit.SetWindowText("0");
	m_input6Edit.ShowWindow(SW_SHOW);
	m_applyButton.ShowWindow(SW_SHOW);
}
void CEE642ProjectDlg::SetInput5Name(CString name)
{
	m_input5Name.SetWindowText(name);
	m_input7Value = 0;
//	UpdateData(FALSE);
	m_input5Name.ShowWindow(SW_SHOW);
	m_input7Edit.SetWindowText("0");
	m_input7Edit.ShowWindow(SW_SHOW);
	m_applyButton.ShowWindow(SW_SHOW);
}
void CEE642ProjectDlg::SetInput6Name(CString name)
{
	m_input6Name.SetWindowText(name);
	m_input8Value = 0;
//	UpdateData(FALSE);
	m_input6Name.ShowWindow(SW_SHOW);
	m_input8Edit.SetWindowText("0");
	m_input8Edit.ShowWindow(SW_SHOW);
	m_applyButton.ShowWindow(SW_SHOW);
}
void CEE642ProjectDlg::OnBnClickedButton6()
{
	m_userContext->Menu6Selected();
}

double CEE642ProjectDlg::GetInput1()
{
	UpdateData();
	return m_input1Value;
}

double CEE642ProjectDlg::GetInput2()
{
	UpdateData();
	return m_input2Value;
}
double CEE642ProjectDlg::GetInput3()
{
	UpdateData();
	return m_edit5Value;
}
double CEE642ProjectDlg::GetInput4()
{
	UpdateData();
	return m_input6Value;
}

double CEE642ProjectDlg::GetInput5()
{
	UpdateData();
	return m_input7Value;
}

double CEE642ProjectDlg::GetInput6()
{
	UpdateData();
	return m_input8Value;
}

void CEE642ProjectDlg::OnBnClickedButtonApply()
{
	m_userContext->ApplyBtnPressed();
}

void CEE642ProjectDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
	OnBnClickedButtonApply();
}

void CEE642ProjectDlg::OnButton7() 
{
	m_userContext->Menu7Selected();
}

void CEE642ProjectDlg::OnButton8() 
{
	m_userContext->Menu8Selected();
}

void CEE642ProjectDlg::OnButton9() 
{
	m_userContext->Menu9Selected();
}

void CEE642ProjectDlg::SetRadio1(CString str)
{
	m_radioBtn.SetWindowText(str);
	m_radioBtn.ShowWindow(SW_SHOW);
	m_radioSelection = 0;
	UpdateData(FALSE);
	m_applyButton.ShowWindow(SW_SHOW);
//	OnRadio1();
}

void CEE642ProjectDlg::SetRadio2(CString str)
{
	CWnd* w = m_radioBtn.GetNextWindow();
	w->SetWindowText(str);
	w->ShowWindow(SW_SHOW);
}

void CEE642ProjectDlg::SetRadio3(CString str)
{
	CWnd* w = m_radioBtn.GetNextWindow();
	w = w->GetNextWindow();
	w->SetWindowText(str);
	w->ShowWindow(SW_SHOW);
}

void CEE642ProjectDlg::SetRadio4(CString str)
{
	CWnd* w = m_radioBtn.GetNextWindow();
	w = w->GetNextWindow();
	w = w->GetNextWindow();
	w->SetWindowText(str);
	w->ShowWindow(SW_SHOW);
}

void CEE642ProjectDlg::SetRadio5(CString str)
{
	CWnd* w = m_radioBtn.GetNextWindow();
	w = w->GetNextWindow();
	w = w->GetNextWindow();
	w = w->GetNextWindow();
	w->SetWindowText(str);
	w->ShowWindow(SW_SHOW);
}

void CEE642ProjectDlg::ClearRadio()
{
	m_radioBtn.ShowWindow(SW_HIDE);
	CWnd* w = m_radioBtn.GetNextWindow();
	w->ShowWindow(SW_HIDE);
	w = w->GetNextWindow();
	w->ShowWindow(SW_HIDE);
	w = w->GetNextWindow();
	w->ShowWindow(SW_HIDE);
	w = w->GetNextWindow();
	w->ShowWindow(SW_HIDE);
}

void CEE642ProjectDlg::OnRadio1() 
{
	LineParametersShow(SW_HIDE);
	m_userContext->OnRadio1();
	m_applyButton.ShowWindow(SW_SHOW);
}

void CEE642ProjectDlg::OnRadio2() 
{
	LineParametersShow(SW_HIDE);	
	m_userContext->OnRadio2();
	m_applyButton.ShowWindow(SW_SHOW);	
}

void CEE642ProjectDlg::OnRadio3() 
{
	LineParametersShow(SW_HIDE);
	m_userContext->OnRadio3();
	m_applyButton.ShowWindow(SW_SHOW);
}

void CEE642ProjectDlg::OnRadio4() 
{
	m_userContext->OnRadio4();	
	m_applyButton.ShowWindow(SW_SHOW);
}

void CEE642ProjectDlg::OnRadio5() 
{
	m_userContext->OnRadio5();
	LineParametersShow(SW_HIDE);	
	m_applyButton.ShowWindow(SW_SHOW);
}

void CEE642ProjectDlg::OnButtonCls() 
{
	SetCurrentGraphObject(0, true);
}

CDC* CEE642ProjectDlg::GetRenderAreaDC()
{
	CDC* pDC = m_renderArea.GetDC();
	CRect clientRect;
	m_renderArea.GetClientRect(clientRect);
	int xOrg = clientRect.Width()/2;
	int yOrg = clientRect.Height()/2;
	pDC->SetViewportExt(clientRect.Size());
	pDC->SetViewportOrg(xOrg, yOrg);
	pDC->SetBkMode(TRANSPARENT);
	return pDC;
}

void CEE642ProjectDlg::ReleaseRenderAreaDC(CDC* pDC)
{
	ReleaseDC(pDC);
}

void CEE642ProjectDlg::WriteMouseLocInfo(int x, int y)
{
	CString str;
	str.Format("X: % 3d <> Y: % 3d",  x, y);
	m_statusAreaWnd.SetWindowText(str);
}

void CEE642ProjectDlg::Exit()
{
	OnCancel();
}

void CEE642ProjectDlg::ShowApplyBtn(int nCmd)
{
	m_applyButton.ShowWindow(nCmd);
}

void CEE642ProjectDlg::ShowMenu9(CString menuName, bool show)
{
	if(show)
	{
		m_menuButtons[8].ShowWindow(SW_SHOW);
		m_menuButtons[8].SetWindowText(menuName);
	}
	else
	{
		m_menuButtons[8].ShowWindow(SW_HIDE);
	}
}
