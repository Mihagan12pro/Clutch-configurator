#pragma once
#include "afxdialogex.h"


// Диалоговое окно CSaveConfigurationsDlg

class CSaveConfigurationsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveConfigurationsDlg)

public:
	CSaveConfigurationsDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CSaveConfigurationsDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PATHS_EDITOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
