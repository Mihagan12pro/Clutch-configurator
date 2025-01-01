// CChooseAssembleDlg.cpp: файл реализации
//

#include "pch.h"
#include "ClutchConfigurator.h"
#include "afxdialogex.h"
#include "CChooseAssembleDlg.h"
#include "MainFrm.h"
#include"iostream"

// Диалоговое окно CChooseAssembleDlg

IMPLEMENT_DYNAMIC(CChooseAssembleDlg, CDialogEx)



CChooseAssembleDlg::CChooseAssembleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHOOSE_ASSEMBLE, pParent)
	, m_nmValue(_T(""))
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
	DDX_Control(pDX, IDC_NM_READONLY_EDIT, m_NMReadonlyEdit);
	DDX_Control(pDX, IDC_NM_READONLY_STATIC, m_NMReadonlyStatic);
	DDX_Text(pDX, IDC_NM_READONLY_EDIT, m_nmValue);
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



void CChooseAssembleDlg::SetExternalItems(HTREEITEM item,Assembler assembler)
{
	m_pAssembler = &assembler;
	m_treeFromGetTree = item;
	m_oldGost = assembler.m_gost;
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
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	ON_CBN_SELCHANGE(IDC_D1_COMBO, &CChooseAssembleDlg::OnCbnSelchangeD1Combo)
	ON_CBN_SELCHANGE(IDC_b1_COMBO, &CChooseAssembleDlg::OnCbnSelchangeb1Combo)
	ON_CBN_SELCHANGE(IDC_D_COMBO, &CChooseAssembleDlg::OnCbnSelchangeDCombo)
	ON_BN_CLICKED(IDOK, &CChooseAssembleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CChooseAssembleDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// Обработчики сообщений CChooseAssembleDlg


BOOL CChooseAssembleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//m_pAssembler = ((CMainFrame*)AfxGetMainWnd())->m_pAssembler;
	m_AssemblesTable.SetExtendedStyle(LVS_EX_GRIDLINES);
	int nmIndex = -1;
	for (int i = 0; i < Assembles::GetAllAssembles().size();i++)
	{
		if (Assembles::GetAllAssembles()[i].GetNM() == m_pAssembler -> GetAssemble().GetNM())
		{
			nmIndex = i;
		}
		m_NMCombo.AddString(Assembles::GetAllAssembles()[i].GetNM());
	}

	m_NMCombo.SetCurSel(nmIndex);
	m_NMReadonlyEdit.SetWindowTextW(Assembles::GetAllAssembles()[nmIndex].GetNM());
	
	m_holeCOMBO.AddString(m_pAssembler->GetAssemble().GetGOST1139(GOST_TOP).GetTittle());
	m_holeCOMBO.AddString(m_pAssembler->GetAssemble().GetGOST1139(GOST_BOTTOM).GetTittle());

	m_holeCOMBO.SetCurSel(m_pAssembler->GetGOST());
	if (m_treeFromGetTree == m_hAssemble)
	{
		SetWindowText(L"Сборка втулочной муфты");
		
		m_NMCombo.ShowWindow(SW_SHOW);
		m_NMSTATIC.ShowWindow(SW_SHOW);
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
		
	}
	else if (m_treeFromGetTree == m_hRing)
	{
		SetWindowText(L"Кольцо");
		m_NMReadonlyEdit.ShowWindow(SW_SHOW);
		m_NMReadonlyStatic.ShowWindow(SW_SHOW);

		CRect rect;
		m_NMReadonlyEdit.GetWindowRect(&rect);

		m_NMReadonlyEdit.SetWindowPos(NULL,530,30,0,0, SWP_NOSIZE | SWP_NOZORDER);
		m_NMReadonlyStatic.SetWindowPos(NULL, 500, 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_DStatic.SetWindowPos(NULL, 500, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_DCOMBO.SetWindowPos(NULL, 530, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_D1Static.SetWindowPos(NULL, 500, 90, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_D1COMBO.SetWindowPos(NULL, 530, 90, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_b1STATIC.SetWindowPos(NULL, 500, 120, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_b1COMBO.SetWindowPos(NULL, 530, 120, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_holeSTATIC.SetWindowPos(NULL, 500, 160, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_holeCOMBO.SetWindowPos(NULL, 500, 180, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		
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

	AddStringToCOMBO(m_b1COMBO, nmIndex, b1s);
	AddStringToCOMBO(m_D1COMBO, nmIndex, D1s);
	AddStringToCOMBO(m_DCOMBO, nmIndex, Ds);


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
	for (int i = 0; i < m_holeCOMBO.GetCount() + 1;i++)
	{
		m_holeCOMBO.DeleteString(0);
	}
	m_NMReadonlyEdit.SetWindowTextW(Assembles::GetAllAssembles()[selectedIndex].GetNM());
	m_holeCOMBO.AddString(Assembles::GetAllAssembles()[selectedIndex].GetGOST1139(GOST_TOP).GetTittle()); //Assembles::GetAllAssembles()[selectedIndex].GetGOST1139(GOST_TOP).GetTittle());
	m_holeCOMBO.AddString(Assembles::GetAllAssembles()[selectedIndex].GetGOST1139(GOST_BOTTOM).GetTittle());
	m_holeCOMBO.SetCurSel(GOST_TOP);
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

//INT_PTR CChooseAssembleDlg::DoModal()
//{
//
//	return CDialogEx::DoModal();
//}

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

void CChooseAssembleDlg::AddStringToCOMBO(CComboBox& combo, int nmIndex, set<double> numbers)
{
	vector<double> vec(numbers.begin(), numbers.end());
	for (int i = 0; i < vec.size();i++)
	{
		combo.AddString(DoubleToCString(vec[i]));

		if (combo == m_DCOMBO && vec[i] == Assembles::GetAllAssembles()[nmIndex].GetD())
		{
			combo.SetCurSel(i);
		}
		else if (combo == m_D1COMBO && vec[i] == Assembles::GetAllAssembles()[nmIndex].GetD1())
		{
			combo.SetCurSel(i);
		}
		else if (combo == m_b1COMBO && vec[i] == Assembles::GetAllAssembles()[nmIndex].Getb1())
		{
			combo.SetCurSel(i);
		}
	}
}

void CChooseAssembleDlg::OnClose()
{
	m_pAssembler->m_gost = m_oldGost;
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	/*if (m_NMReadonlyEdit.GetWindowTextLengthW() == 0 && m_treeFromGetTree != m_hAssemble)
	{
		if (MessageBox(L"Выбранные вами параметры не подходят ни одному крутящему моменту.\nЕсли вы закроете данное окно, выставленные вами параметры будут сброшены.", L"Вы уверены, что хотите закрыть данное окно?", MB_OKCANCEL) != IDOK)
		{
			return;
		}
	}*/
	CDialogEx::OnClose();
}
double CChooseAssembleDlg::CStringTODouble(CString str)
{
	return _wtof(str);
}
//atof(thestring).
// 
//void CChooseAssembleDlg::OnCancelMode()
//{
//	CDialogEx::OnCancelMode();
//}


void CChooseAssembleDlg::OnCbnSelchangeD1Combo()
{
	// TODO: добавьте свой код обработчика уведомлений
	SetCurselsChanged();
}


void CChooseAssembleDlg::OnCbnSelchangeb1Combo()
{
	// TODO: добавьте свой код обработчика уведомлений
	SetCurselsChanged();
}


void CChooseAssembleDlg::OnCbnSelchangeDCombo()
{
	// TODO: добавьте свой код обработчика уведомлений
	SetCurselsChanged();
}


void CChooseAssembleDlg::SetCurselsChanged()
{
	if (m_treeFromGetTree != m_hAssemble)
	{
		CString C_D,C_D1,C_b1;
		double D,D1,b1;
		if (m_treeFromGetTree == m_hRing)
		{
			m_DCOMBO.GetLBText(m_DCOMBO.GetCurSel(),C_D);
			D = CStringTODouble(C_D);

			m_D1COMBO.GetLBText(m_D1COMBO.GetCurSel(), C_D1);
			D1 = CStringTODouble(C_D1);

			m_b1COMBO.GetLBText(m_b1COMBO.GetCurSel(), C_b1);
			b1 = CStringTODouble(C_b1);

			bool has = true;

			if (m_pAssembler->D != D || m_pAssembler->D1 != D1 && m_pAssembler->b1 != b1)
			{
				m_NMReadonlyEdit.SetWindowTextW(L"");

				for (int i = 0; i < Assembles::GetAllAssembles().size();i++)
				{
					if (Assembles::GetAllAssembles()[i].Getb1() == b1 && Assembles::GetAllAssembles()[i].GetD1() == D1 && Assembles::GetAllAssembles()[i].GetD() == D)
					{
						//m_NMReadonlyEdit.SetWindowTextW(Assembles::GetAllAssembles()[i].GetNM());
						ChangeNM(i);
						break;
					}
				}
			}
		}
	}
}
CClutchAssemble CChooseAssembleDlg::GetAssemble()
{
	return m_pAssembler->GetAssemble();
}
GOST  CChooseAssembleDlg::GetGost()
{
	return m_pAssembler->GetGOST();
}
void CChooseAssembleDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}


void CChooseAssembleDlg::OnBnClickedCancel()
{
	m_pAssembler->m_gost = m_oldGost;
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}
