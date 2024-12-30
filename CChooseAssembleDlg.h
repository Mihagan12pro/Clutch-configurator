#pragma once
#include "afxdialogex.h"
class CClutchAssembler;
class CClutchAssemble;
class CMainFrame;
#include<vector>
// Диалоговое окно CChooseAssembleDlg

class CChooseAssembleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChooseAssembleDlg)

public:

	void GetTreeItem(HTREEITEM item);

	CChooseAssembleDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CChooseAssembleDlg();
	static void SetHTREEITEMs(HTREEITEM m_hAssemble, HTREEITEM m_hCollar, HTREEITEM m_hRing, HTREEITEM m_hScrew);
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHOOSE_ASSEMBLE };
#endif

protected:
	static bool m_isHTREEITEMsReady;
	static HTREEITEM m_hAssemble, m_hCollar, m_hRing, m_hScrew;
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV


	HTREEITEM m_treeFromGetTree;
	CClutchAssembler *m_assembler;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CListCtrl m_AssemblesTable;
	CComboBox m_holeCOMBO;
	CComboBox m_NMCombo;
	CStatic m_holeSTATIC;
	CStatic m_NMSTATIC;

public:
	afx_msg void OnCbnSelchangeNmCombo();
private:
	CString DoubleToCString(double number);
	void ChangeNM(int selectedIndex);
};
