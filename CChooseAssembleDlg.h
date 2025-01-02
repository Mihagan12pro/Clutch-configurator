#pragma once
#include "afxdialogex.h"

class CClutchAssembler;

#include"CClutchAssemble.h"

#include<vector>
#include <set>
using namespace std;
// Диалоговое окно CChooseAssembleDlg

class CChooseAssembleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChooseAssembleDlg)

public:

	void SetExternalItems(HTREEITEM item, CClutchAssembler assembler);

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

	GOST m_oldGost;
	int m_oldSelectedIndex;
	HTREEITEM m_treeFromGetTree;
	
	CClutchAssembler *m_pAssembler;

	CClutchAssemble m_assemble;
	GOST gost;

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
	void AddStringToCOMBO(CComboBox& combo, int nmIndex, set<double> numbers);
	void SetCurselsChanged();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CString DoubleToCString(double number);
	void ChangeNM(int selectedIndex);
	afx_msg void OnCbnSelchangeNmCombo();
	double CStringTODouble(CString str);
public:
	CClutchAssembler GetNewAssembler();
	CClutchAssemble GetAssemble();
	GOST GetGost();
//	virtual INT_PTR DoModal();
	afx_msg void OnCbnSelchangeHole1139Combo();
private:
	CStatic m_D1STATIC;
	CComboBox m_D1COMBO;
	CStatic m_b1STATIC;
	CComboBox m_b1COMBO;
	CStatic m_DSTATIC;
	CComboBox m_DCOMBO;
private :
	set<double> D1s = {};
	set<double> Ds = {};
	set<double> b1s = {};
	set<double> c1s = {};
	set<double> d1s = {};
	CEdit m_NMReadonlyEDIT;
	CStatic m_NMReadonlySTATIC;
public:
	CString m_nmValue;
	afx_msg void OnClose();
//	afx_msg void OnCancelMode();
	afx_msg void OnCbnSelchangeD1Combo();
	afx_msg void OnCbnSelchangeb1Combo();
	afx_msg void OnCbnSelchangeDCombo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	
private:
	
	/*CStatic m_dSTATIC;
	CComboBox m_dCOMBO;*/
	CStatic m_c1STATIC;
	CComboBox m_c1COMBO;
public:
	/*CStatic m_d1STATIC;
	CComboBox m_d1COMBO;*/
private:
	CStatic m_d1STATIC;
	CComboBox m_d1COMBO;
public:
	afx_msg void OnCbnSelchangec1Combo();
	afx_msg void OnSelchanged1Combo();
};
