#pragma once
#include "afxwin.h"
#include "auxiliaryClasses.h"

// CPlanePictEntranceDlg dialog

class CPlanePictEntranceDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlanePictEntranceDlg)

public:
	CPlanePictEntranceDlg(TRegionMap& rMap, Bitmap* &mask, CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlanePictEntranceDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL DisplayMask();
	DECLARE_MESSAGE_MAP()
public:
	// window that will handle the picture that the user inputs
	CStatic m_pictFrame;
	afx_msg void OnOpenFile();
	afx_msg void OnApplyParams();

private:
	Bitmap*		&m_maskBmp;
	TRegionMap&	m_regionMap;
	int			m_intensity;
public:
	afx_msg void OnPaint();
	// //combo-box that lists the available intensity values, i.e. regions of the mask image
	CComboBox m_intensityCombo;
	CButton	m_isImoCheck;
	CEdit m_paramsEdit;
	CListBox	m_summaryList;
	afx_msg void OnIntensitySelectionChange();
};
