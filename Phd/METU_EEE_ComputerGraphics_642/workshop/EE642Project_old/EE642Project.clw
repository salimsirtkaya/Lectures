; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEE642ProjectDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EE642Project.h"

ClassCount=4
Class1=CEE642ProjectApp
Class2=CEE642ProjectDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_EE642PROJECT_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Class4=CRenderingArea
Resource5=IDD_EE642PROJECT_DIALOG (English (U.S.))

[CLS:CEE642ProjectApp]
Type=0
HeaderFile=EE642Project.h
ImplementationFile=EE642Project.cpp
Filter=N

[CLS:CEE642ProjectDlg]
Type=0
HeaderFile=EE642ProjectDlg.h
ImplementationFile=EE642ProjectDlg.cpp
Filter=D
LastObject=IDC_RENDERING_AREA
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=EE642ProjectDlg.h
ImplementationFile=EE642ProjectDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_EE642PROJECT_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CEE642ProjectDlg

[DLG:IDD_EE642PROJECT_DIALOG (English (U.S.))]
Type=1
Class=CEE642ProjectDlg
ControlCount=4
Control1=IDC_RENDER_AREA,static,1342308352
Control2=IDC_MENU_AREA,static,1342308352
Control3=IDC_INFO_AREA,static,1342308352
Control4=IDC_STATUS_AREA,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CRenderingArea]
Type=0
HeaderFile=RenderingArea.h
ImplementationFile=RenderingArea.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

