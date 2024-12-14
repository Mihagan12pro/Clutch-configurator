#pragma once
#include "afxdialogex.h"
#include<string>
using namespace std;

// Диалоговое окно CAssembleDlg

class CAssembleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAssembleDlg)

public:
	CAssembleDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CAssembleDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AssembleDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CString m_saveAssembleVALUE;
public:
	virtual BOOL OnInitDialog();
};
