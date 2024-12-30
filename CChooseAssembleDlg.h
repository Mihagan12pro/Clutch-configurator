#pragma once
#include "afxdialogex.h"

class CClutchAssembler;
//class CClutchAssemble;
#include"CClutchAssemble.h"
class CMainFrame;
#include<vector>
#include <unordered_set>
using namespace std;
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
	CClutchAssembler *m_pAssembler;

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
	
private:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CString DoubleToCString(double number);
	void ChangeNM(int selectedIndex);
	afx_msg void OnCbnSelchangeNmCombo();
public:
	CClutchAssembler GetNewAssembler();
	virtual INT_PTR DoModal();
	afx_msg void OnCbnSelchangeHole1139Combo();
private:
	CStatic m_D1Static;
	CComboBox m_D1COMBO;
	CStatic m_b1STATIC;
	CComboBox m_b1COMBO;
	CStatic m_DStatic;
	CComboBox m_DCOMBO;
private :
	unordered_set<double> D1s = {};
	unordered_set<double> Ds = {};
	unordered_set<double> b1s = {};
};
