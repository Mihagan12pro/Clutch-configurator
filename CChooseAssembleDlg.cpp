// CChooseAssembleDlg.cpp: файл реализации
//

#include "pch.h"
#include "ClutchConfigurator.h"
#include "afxdialogex.h"
#include "CChooseAssembleDlg.h"
#include "CClutchAssembler.h"
#include "MainFrm.h"
#include "CClutchAssembler.h"
#include"CClutchAssemble.h"
#include"iostream"

// Диалоговое окно CChooseAssembleDlg

IMPLEMENT_DYNAMIC(CChooseAssembleDlg, CDialogEx)



CChooseAssembleDlg::CChooseAssembleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHOOSE_ASSEMBLE, pParent)
{

}

CChooseAssembleDlg::~CChooseAssembleDlg()
{
}

void CChooseAssembleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ASSEMBLES_LIST, m_AssemblesTable);
	DDX_Control(pDX, IDC_NM_COMBO, m_NMCombo);
	DDX_Control(pDX, IDC_HOLE1139_STATIC, m_holeSTATIC);


	DDX_Control(pDX, IDC_NM_STATIC, m_NMSTATIC);
	DDX_Control(pDX, IDC_HOLE1139_COMBO, m_holeCOMBO);
	DDX_Control(pDX, IDC_D1_STATIC, m_D1Static);
	DDX_Control(pDX, IDC_D1_COMBO, m_D1COMBO);
	DDX_Control(pDX, IDC_b1_STATIC, m_b1STATIC);
	DDX_Control(pDX, IDC_b1_COMBO, m_b1COMBO);
	DDX_Control(pDX, IDC_D_STATIC, m_DStatic);
	DDX_Control(pDX, IDC_D_COMBO, m_DCOMBO);
}
void CChooseAssembleDlg::SetHTREEITEMs(HTREEITEM Assemble, HTREEITEM Collar, HTREEITEM Ring, HTREEITEM Screw)
{
	if (!m_isHTREEITEMsReady)
	{
		m_isHTREEITEMsReady = true;

		CChooseAssembleDlg::m_hAssemble = Assemble;
		CChooseAssembleDlg::m_hCollar = Collar;
		CChooseAssembleDlg::m_hRing = Ring;
		CChooseAssembleDlg::m_hScrew = Screw;

	}
}



void CChooseAssembleDlg::GetTreeItem(HTREEITEM item)
{
	m_treeFromGetTree = item;
}


bool CChooseAssembleDlg::m_isHTREEITEMsReady = false;

HTREEITEM CChooseAssembleDlg::m_hAssemble;
HTREEITEM CChooseAssembleDlg::m_hCollar;
HTREEITEM CChooseAssembleDlg::m_hRing;
HTREEITEM CChooseAssembleDlg::m_hScrew;

BEGIN_MESSAGE_MAP(CChooseAssembleDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_NM_COMBO, &CChooseAssembleDlg::OnCbnSelchangeNmCombo)
	ON_WM_LBUTTONDBLCLK()
	ON_CBN_SELCHANGE(IDC_HOLE1139_COMBO, &CChooseAssembleDlg::OnCbnSelchangeHole1139Combo)
END_MESSAGE_MAP()


// Обработчики сообщений CChooseAssembleDlg


BOOL CChooseAssembleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pAssembler = ((CMainFrame*)AfxGetMainWnd())->m_pAssembler;
	m_AssemblesTable.SetExtendedStyle(LVS_EX_GRIDLINES);
	int nmThatWeNeed = -1;
	for (int i = 0; i < Assembles::GetAllAssembles().size();i++)
	{
		if (Assembles::GetAllAssembles()[i].GetNM() == m_pAssembler -> GetAssemble().GetNM())
		{
			nmThatWeNeed = i;
		}
		m_NMCombo.AddString(Assembles::GetAllAssembles()[i].GetNM());
	}
	m_NMCombo.SetCurSel(nmThatWeNeed);

	
	if (m_treeFromGetTree == m_hAssemble)
	{
		SetWindowText(L"Сборка втулочной муфты");
		m_holeSTATIC.ShowWindow(SW_SHOW);
		m_holeCOMBO.ShowWindow(SW_SHOW);
		/*m_AssemblesTable.ShowWindow(SW_SHOW);*/
		m_AssemblesTable.InsertColumn(0,L"Мкр", LVCFMT_LEFT,65);
		m_AssemblesTable.InsertColumn(1, L"D", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(2, L"D1", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(3, L"b1", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(4, L"d1", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(5, L"L", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(6, L"l", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(7, L"r", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(8, L"f", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(9, L"c", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(10, L"c1", LVCFMT_LEFT, 40);
		for (int i = 0; i < Assembles::GetAllAssembles().size();i++)
		{
			int item = m_AssemblesTable.InsertItem(i, Assembles::GetAllAssembles()[i].GetNM());
			m_AssemblesTable.SetItemText(item,1,DoubleToCString(Assembles::GetAllAssembles()[i].GetD()));
			m_AssemblesTable.SetItemText(item, 2, DoubleToCString(Assembles::GetAllAssembles()[i].GetD1()));
			m_AssemblesTable.SetItemText(item, 3, DoubleToCString(Assembles::GetAllAssembles()[i].Getb1()));
			m_AssemblesTable.SetItemText(item, 4, DoubleToCString(Assembles::GetAllAssembles()[i].Getd1()));
			m_AssemblesTable.SetItemText(item, 5, DoubleToCString(Assembles::GetAllAssembles()[i].GetL()));
			m_AssemblesTable.SetItemText(item, 6, DoubleToCString(Assembles::GetAllAssembles()[i].Getl()));
			m_AssemblesTable.SetItemText(item, 7, DoubleToCString(Assembles::GetAllAssembles()[i].Getr()));
			m_AssemblesTable.SetItemText(item, 8, DoubleToCString(Assembles::GetAllAssembles()[i].Getf()));
			m_AssemblesTable.SetItemText(item, 9, DoubleToCString(Assembles::GetAllAssembles()[i].Getc()));
			m_AssemblesTable.SetItemText(item, 10, DoubleToCString(Assembles::GetAllAssembles()[i].Getc1()));
		}
		m_holeCOMBO.AddString(m_pAssembler->GetAssemble().GetGOST1139(GOST_TOP).GetTittle());
		m_holeCOMBO.AddString(m_pAssembler->GetAssemble().GetGOST1139(GOST_BOTTOM).GetTittle());
		
		m_holeCOMBO.SetCurSel(m_pAssembler->GetGOST());
	}
	else if (m_treeFromGetTree == m_hRing)
	{
		SetWindowText(L"Кольцо");
		m_D1Static.ShowWindow(SW_SHOW);
		m_D1COMBO.ShowWindow(SW_SHOW);
		m_b1STATIC.ShowWindow(SW_SHOW);
		m_b1COMBO.ShowWindow(SW_SHOW);
		m_DStatic.ShowWindow(SW_SHOW);
		m_DCOMBO.ShowWindow(SW_SHOW);
		m_AssemblesTable.InsertColumn(0, L"Мкр", LVCFMT_LEFT, 200);
		m_AssemblesTable.InsertColumn(1, L"D", LVCFMT_LEFT, 100);
		m_AssemblesTable.InsertColumn(2, L"D1", LVCFMT_LEFT, 100);
		m_AssemblesTable.InsertColumn(3, L"b1", LVCFMT_LEFT, 100);

		

		for (int i = 0; i < Assembles::GetAllAssembles().size();i++)
		{
			int item = m_AssemblesTable.InsertItem(i, Assembles::GetAllAssembles()[i].GetNM());
			m_AssemblesTable.SetItemText(item, 1, DoubleToCString(Assembles::GetAllAssembles()[i].GetD()));
			m_AssemblesTable.SetItemText(item, 2, DoubleToCString(Assembles::GetAllAssembles()[i].GetD1()));
			m_AssemblesTable.SetItemText(item, 3, DoubleToCString(Assembles::GetAllAssembles()[i].Getb1()));

			D1s.insert(Assembles::GetAllAssembles()[i].GetD1());
			Ds.insert(Assembles::GetAllAssembles()[i].GetD());
			b1s.insert(Assembles::GetAllAssembles()[i].Getb1());
		}
	}
	else if (m_treeFromGetTree == m_hCollar)
	{
		SetWindowText(L"Втулка");
	}
	else if (m_treeFromGetTree == m_hScrew)
	{
		SetWindowText(L"Винт");
	}
	// TODO:  Добавить дополнительную инициализацию

	for (double b1 : b1s)
	{
		m_b1COMBO.AddString(DoubleToCString(b1));
	}
	for (double D1 : D1s)
	{
		m_D1COMBO.AddString(DoubleToCString(D1));
	}
	for (double D : Ds)
	{
		m_DCOMBO.AddString(DoubleToCString(D));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
CString  CChooseAssembleDlg::DoubleToCString(double number)
{
	CString strNumber;

	strNumber.Format(L"%g", number);

	return strNumber;
}

void CChooseAssembleDlg::OnCbnSelchangeNmCombo()
{
	ChangeNM(m_NMCombo.GetCurSel());
	// TODO: добавьте свой код обработчика уведомлений	
}
void CChooseAssembleDlg::ChangeNM(int selectedIndex)
{
	*m_pAssembler = Assembler(Assembles::GetAllAssembles()[selectedIndex],GOST_TOP);
	if (m_treeFromGetTree == m_hAssemble)
	{
		for (int i = 0; i < m_holeCOMBO.GetCount() + 1;i++)
		{
			m_holeCOMBO.DeleteString(0);
		}
		m_holeCOMBO.AddString(m_pAssembler->GetAssemble().GetGOST1139(GOST_TOP).GetTittle()); //Assembles::GetAllAssembles()[selectedIndex].GetGOST1139(GOST_TOP).GetTittle());
		m_holeCOMBO.AddString(m_pAssembler->GetAssemble().GetGOST1139(GOST_BOTTOM).GetTittle());

		m_holeCOMBO.SetCurSel(GOST_TOP);
	}
}


void CChooseAssembleDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CDialogEx::OnLButtonDblClk(nFlags, point);


	//if (m_AssemblesTable.)
}

Assembler CChooseAssembleDlg::GetNewAssembler()
{
	
	return *m_pAssembler;
}

INT_PTR CChooseAssembleDlg::DoModal()
{
	// TODO: добавьте специализированный код или вызов базового класса
	
	return CDialogEx::DoModal();
}


void CChooseAssembleDlg::OnCbnSelchangeHole1139Combo()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_pAssembler->UpdateGOST(m_holeCOMBO.GetCurSel());

	if (m_pAssembler->d == m_pAssembler->D2 && m_pAssembler->b == m_pAssembler->d)
	{
		m_pAssembler->UpdateGOST(GOST_TOP);
		m_holeCOMBO.SetCurSel(GOST_TOP);
	}
}
