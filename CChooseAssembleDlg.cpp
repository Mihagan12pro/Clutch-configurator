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
	DDX_Control(pDX, IDC_D1_STATIC, m_D1STATIC);
	DDX_Control(pDX, IDC_D1_COMBO, m_D1COMBO);
	DDX_Control(pDX, IDC_b1_STATIC, m_b1STATIC);
	DDX_Control(pDX, IDC_b1_COMBO, m_b1COMBO);
	DDX_Control(pDX, IDC_D_STATIC, m_DSTATIC);
	DDX_Control(pDX, IDC_D_COMBO, m_DCOMBO);
	DDX_Control(pDX, IDC_NM_READONLY_EDIT, m_NMReadonlyEDIT);
	DDX_Control(pDX, IDC_NM_READONLY_STATIC, m_NMReadonlySTATIC);
	DDX_Text(pDX, IDC_NM_READONLY_EDIT, m_nmValue);
	/*DDX_Control(pDX, IDC__d__STATIC, m_dSTATIC);
	DDX_Control(pDX, IDC__d__COMBO, m_dCOMBO);*/
	DDX_Control(pDX, IDC_c1_STATIC, m_c1STATIC);
	DDX_Control(pDX, IDC_c1_COMBO, m_c1COMBO);
	/*DDX_Control(pDX, IDC__d1__STATIC, m_d1STATIC);
	DDX_Control(pDX, IDC__d1__COMBO, m_d1COMBO);*/
	DDX_Control(pDX, IDC__d1__STATIC, m_d1STATIC);
	DDX_Control(pDX, IDC__d1__COMBO, m_d1COMBO);
	DDX_Control(pDX, IDC_c_STATIC, m_cSTATIC);
	DDX_Control(pDX, IDC_c_COMBO, m_cCOMBO);
	DDX_Control(pDX, IDC_r_STATIC, m_rSTATIC);
	DDX_Control(pDX, IDC_r_COMBO, m_rCOMBO);
	DDX_Control(pDX, IDC_f_STATIC, m_fSTATIC);
	DDX_Control(pDX, IDC_f_COMBO, m_fCOMBO);
	DDX_Control(pDX, IDC_L_STATIC, m_LSTATIC);
	DDX_Control(pDX, IDC_L_COMBO, m_LCOMBO);
	DDX_Control(pDX, IDC__l__STATIC, m_lSTATIC);
	/*DDX_Control(pDX, IDC__l__COMBO, m_lCOMBO);*/
	DDX_Control(pDX, IDC__l__COMBO, m_lCOMBO);
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
	ON_CBN_SELCHANGE(IDC_c1_COMBO, &CChooseAssembleDlg::OnCbnSelchangec1Combo)
	ON_CBN_SELCHANGE(IDC__d1__COMBO, &CChooseAssembleDlg::OnSelchanged1Combo)
	ON_CBN_SELCHANGE(IDC_L_COMBO, &CChooseAssembleDlg::OnCbnSelchangeLCombo)
	ON_CBN_SELCHANGE(IDC_f_COMBO, &CChooseAssembleDlg::OnCbnSelchangefCombo)
	ON_CBN_SELCHANGE(IDC_r_COMBO, &CChooseAssembleDlg::OnCbnSelchangerCombo)
	ON_CBN_SELCHANGE(IDC_c_COMBO, &CChooseAssembleDlg::OnCbnSelchangecCombo)
	ON_CBN_SELCHANGE(IDC__l__COMBO, &CChooseAssembleDlg::OnCbnSelchangelCombo)
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
	m_NMReadonlyEDIT.SetWindowTextW(Assembles::GetAllAssembles()[nmIndex].GetNM());
	
	m_holeCOMBO.AddString(m_pAssembler->GetAssemble().GetGOST1139(GOST_TOP).GetTittle());
	m_holeCOMBO.AddString(m_pAssembler->GetAssemble().GetGOST1139(GOST_BOTTOM).GetTittle());

	m_holeCOMBO.SetCurSel(m_pAssembler->GetGOST());
	if (m_treeFromGetTree != m_hAssemble)
	{
		m_NMReadonlyEDIT.ShowWindow(SW_SHOW);
		m_NMReadonlySTATIC.ShowWindow(SW_SHOW);
		m_NMReadonlyEDIT.SetWindowPos(NULL, 530, 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_NMReadonlySTATIC.SetWindowPos(NULL, 500, 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
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

		m_holeSTATIC.SetWindowPos(NULL, 490, 70, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_holeCOMBO.SetWindowPos(NULL, 490, 90, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	else if (m_treeFromGetTree == m_hRing)
	{
		SetWindowText(L"Кольцо");
		

		CRect rect;
		m_NMReadonlyEDIT.GetWindowRect(&rect);

		

		m_DSTATIC.SetWindowPos(NULL, 500, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_DCOMBO.SetWindowPos(NULL, 530, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_D1STATIC.SetWindowPos(NULL, 500, 90, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_D1COMBO.SetWindowPos(NULL, 530, 90, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_b1STATIC.SetWindowPos(NULL, 500, 120, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_b1COMBO.SetWindowPos(NULL, 530, 120, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_holeSTATIC.SetWindowPos(NULL, 500, 160, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_holeCOMBO.SetWindowPos(NULL, 500, 180, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		
		m_D1STATIC.ShowWindow(SW_SHOW);
		m_D1COMBO.ShowWindow(SW_SHOW);
		m_b1STATIC.ShowWindow(SW_SHOW);
		m_b1COMBO.ShowWindow(SW_SHOW);
		m_DSTATIC.ShowWindow(SW_SHOW);
		m_DCOMBO.ShowWindow(SW_SHOW);
		m_AssemblesTable.InsertColumn(0, L"Мкр", LVCFMT_LEFT, 170);
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
	
	else if (m_treeFromGetTree == m_hScrew)
	{
		SetWindowText(L"Винт");
		m_D1STATIC.ShowWindow(SW_SHOW);
		m_D1COMBO.ShowWindow(SW_SHOW);

		m_b1STATIC.ShowWindow(SW_SHOW);
		m_b1COMBO.ShowWindow(SW_SHOW);

		m_DSTATIC.ShowWindow(SW_SHOW);
		m_DCOMBO.ShowWindow(SW_SHOW);

		m_d1COMBO.ShowWindow(SW_SHOW);
		m_d1STATIC.ShowWindow(SW_SHOW);
		
		m_c1STATIC.ShowWindow(SW_SHOW);
		m_c1COMBO.ShowWindow(SW_SHOW);

		


		m_NMReadonlyEDIT.SetWindowPos(NULL, 530, 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_NMReadonlySTATIC.SetWindowPos(NULL, 500, 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_DSTATIC.SetWindowPos(NULL, 500, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_DCOMBO.SetWindowPos(NULL, 530, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_D1STATIC.SetWindowPos(NULL, 500, 90, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_D1COMBO.SetWindowPos(NULL, 530, 90, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_b1STATIC.SetWindowPos(NULL, 500, 120, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_b1COMBO.SetWindowPos(NULL, 530, 120, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_c1STATIC.SetWindowPos(NULL, 500, 150, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_c1COMBO.SetWindowPos(NULL, 530, 150, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_d1STATIC.SetWindowPos(NULL, 500, 180, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_d1COMBO.SetWindowPos(NULL, 530, 180, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		m_holeSTATIC.SetWindowPos(NULL, 500, 210, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_holeCOMBO.SetWindowPos(NULL, 500, 230, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	
		m_AssemblesTable.InsertColumn(0, L"Мкр", LVCFMT_LEFT, 172);
		m_AssemblesTable.InsertColumn(1, L"D", LVCFMT_LEFT, 60);
		m_AssemblesTable.InsertColumn(2, L"D1", LVCFMT_LEFT, 60);
		m_AssemblesTable.InsertColumn(3, L"b1", LVCFMT_LEFT, 60);
		m_AssemblesTable.InsertColumn(5, L"c1", LVCFMT_LEFT, 60);
		m_AssemblesTable.InsertColumn(6, L"d1", LVCFMT_LEFT, 60);

		for (int i = 0; i < Assembles::GetAllAssembles().size();i++)
		{
			int item = m_AssemblesTable.InsertItem(i, Assembles::GetAllAssembles()[i].GetNM());
			m_AssemblesTable.SetItemText(item, 1, DoubleToCString(Assembles::GetAllAssembles()[i].GetD()));
			m_AssemblesTable.SetItemText(item, 2, DoubleToCString(Assembles::GetAllAssembles()[i].GetD1()));
			m_AssemblesTable.SetItemText(item, 3, DoubleToCString(Assembles::GetAllAssembles()[i].Getb1()));
			m_AssemblesTable.SetItemText(item, 4, DoubleToCString(Assembles::GetAllAssembles()[i].Getc1()));
			m_AssemblesTable.SetItemText(item, 5, DoubleToCString(Assembles::GetAllAssembles()[i].Getd1()));

			D1s.insert(Assembles::GetAllAssembles()[i].GetD1());
			Ds.insert(Assembles::GetAllAssembles()[i].GetD());
			b1s.insert(Assembles::GetAllAssembles()[i].Getb1());
			c1s.insert(Assembles::GetAllAssembles()[i].Getc1());
			d1s.insert(Assembles::GetAllAssembles()[i].Getd1());
		}
	}
	else if (m_treeFromGetTree == m_hCollar)
	{
		SetWindowText(L"Втулка");

		m_cSTATIC.ShowWindow(SW_SHOW);
		m_cCOMBO.ShowWindow(SW_SHOW);

		m_rSTATIC.ShowWindow(SW_SHOW);
		m_rCOMBO.ShowWindow(SW_SHOW);

		m_fSTATIC.ShowWindow(SW_SHOW);
		m_fCOMBO.ShowWindow(SW_SHOW);

		m_LSTATIC.ShowWindow(SW_SHOW);
		m_LCOMBO.ShowWindow(SW_SHOW);

		m_lSTATIC.ShowWindow(SW_SHOW);
		m_lCOMBO.ShowWindow(SW_SHOW);

		m_D1STATIC.ShowWindow(SW_SHOW);
		m_D1COMBO.ShowWindow(SW_SHOW);

		m_b1STATIC.ShowWindow(SW_SHOW);
		m_b1COMBO.ShowWindow(SW_SHOW);

		m_DSTATIC.ShowWindow(SW_SHOW);
		m_DCOMBO.ShowWindow(SW_SHOW);

		m_d1COMBO.ShowWindow(SW_SHOW);
		m_d1STATIC.ShowWindow(SW_SHOW);

		m_c1STATIC.ShowWindow(SW_SHOW);
		m_c1COMBO.ShowWindow(SW_SHOW);

		m_NMReadonlySTATIC.SetWindowPos(NULL,492,60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		m_NMReadonlyEDIT.SetWindowPos(NULL, 522, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);


		m_AssemblesTable.InsertColumn(0, L"Мкр", LVCFMT_LEFT, 70);
		m_AssemblesTable.InsertColumn(1, L"D", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(2, L"D1", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(3, L"b1", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(5, L"c1", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(6, L"d1", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(7, L"c", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(8, L"r", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(9, L"f", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(10, L"L", LVCFMT_LEFT, 40);
		m_AssemblesTable.InsertColumn(11, L"l", LVCFMT_LEFT, 40);

		for (int i = 0; i < Assembles::GetAllAssembles().size();i++)
		{
			int item = m_AssemblesTable.InsertItem(i, Assembles::GetAllAssembles()[i].GetNM());
			m_AssemblesTable.SetItemText(item, 1, DoubleToCString(Assembles::GetAllAssembles()[i].GetD()));
			m_AssemblesTable.SetItemText(item, 2, DoubleToCString(Assembles::GetAllAssembles()[i].GetD1()));
			m_AssemblesTable.SetItemText(item, 3, DoubleToCString(Assembles::GetAllAssembles()[i].Getb1()));
			m_AssemblesTable.SetItemText(item, 4, DoubleToCString(Assembles::GetAllAssembles()[i].Getc1()));
			m_AssemblesTable.SetItemText(item, 5, DoubleToCString(Assembles::GetAllAssembles()[i].Getd1()));
			m_AssemblesTable.SetItemText(item, 6, DoubleToCString(Assembles::GetAllAssembles()[i].Getc()));
			m_AssemblesTable.SetItemText(item, 7, DoubleToCString(Assembles::GetAllAssembles()[i].Getr()));
			m_AssemblesTable.SetItemText(item, 8, DoubleToCString(Assembles::GetAllAssembles()[i].Getf()));
			m_AssemblesTable.SetItemText(item, 9, DoubleToCString(Assembles::GetAllAssembles()[i].GetL()));
			m_AssemblesTable.SetItemText(item, 10, DoubleToCString(Assembles::GetAllAssembles()[i].Getl()));

			D1s.insert(Assembles::GetAllAssembles()[i].GetD1());
			Ds.insert(Assembles::GetAllAssembles()[i].GetD());
			b1s.insert(Assembles::GetAllAssembles()[i].Getb1());
			c1s.insert(Assembles::GetAllAssembles()[i].Getc1());
			d1s.insert(Assembles::GetAllAssembles()[i].Getd1());
			cs.insert(Assembles::GetAllAssembles()[i].Getc());
			rs.insert(Assembles::GetAllAssembles()[i].Getr());
			fs.insert(Assembles::GetAllAssembles()[i].Getf());
			Ls.insert(Assembles::GetAllAssembles()[i].GetL());
			ls.insert(Assembles::GetAllAssembles()[i].Getl());
		}
	}
	// TODO:  Добавить дополнительную инициализацию

	AddStringToCOMBO(m_b1COMBO, nmIndex, b1s);
	AddStringToCOMBO(m_D1COMBO, nmIndex, D1s);
	AddStringToCOMBO(m_DCOMBO, nmIndex, Ds);
	AddStringToCOMBO(m_d1COMBO,nmIndex,d1s);
	AddStringToCOMBO(m_c1COMBO, nmIndex, c1s);
	AddStringToCOMBO(m_cCOMBO, nmIndex, cs);
	AddStringToCOMBO(m_rCOMBO, nmIndex, rs);
	AddStringToCOMBO(m_fCOMBO, nmIndex, fs);
	AddStringToCOMBO(m_LCOMBO, nmIndex, Ls);
	AddStringToCOMBO(m_lCOMBO, nmIndex, ls);

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
	m_pAssembler = new Assembler(Assembles::GetAllAssembles()[selectedIndex],GOST_TOP);
	for (int i = 0; i < m_holeCOMBO.GetCount()+1 ;i++)
	{
		m_holeCOMBO.DeleteString(0);
	}
	
	m_NMReadonlyEDIT.SetWindowTextW(Assembles::GetAllAssembles()[selectedIndex].GetNM());
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
		else if (combo == m_c1COMBO && vec[i] == Assembles::GetAllAssembles()[nmIndex].Getc1())
		{
			combo.SetCurSel(i);
		}
		else if (combo == m_d1COMBO && vec[i] == Assembles::GetAllAssembles()[nmIndex].Getd1())
		{
			combo.SetCurSel(i);
		}
		else if (combo == m_cCOMBO && vec[i] == Assembles::GetAllAssembles()[nmIndex].Getc())
		{
			combo.SetCurSel(i);
		}
		else if (combo == m_rCOMBO && vec[i] == Assembles::GetAllAssembles()[nmIndex].Getr())
		{
			combo.SetCurSel(i);
		}
		else if (combo == m_fCOMBO && vec[i] == Assembles::GetAllAssembles()[nmIndex].Getf())
		{
			combo.SetCurSel(i);
		}
		else if (combo == m_LCOMBO && vec[i] == Assembles::GetAllAssembles()[nmIndex].GetL())
		{
			combo.SetCurSel(i);
		}
		else if (combo == m_lCOMBO && vec[i] == Assembles::GetAllAssembles()[nmIndex].Getl())
		{
			combo.SetCurSel(i);
		}
	}
}

void CChooseAssembleDlg::OnClose()
{
	m_pAssembler->m_gost = m_oldGost;
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

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

void CChooseAssembleDlg::OnCbnSelchangec1Combo()
{
	// TODO: добавьте свой код обработчика уведомлений
	SetCurselsChanged();
}


void CChooseAssembleDlg::OnCbnSelchangeLCombo()
{
	// TODO: добавьте свой код обработчика уведомлений
	SetCurselsChanged();
}


void CChooseAssembleDlg::OnCbnSelchangefCombo()
{
	// TODO: добавьте свой код обработчика уведомлений
	SetCurselsChanged();
}


void CChooseAssembleDlg::OnCbnSelchangerCombo()
{
	// TODO: добавьте свой код обработчика уведомлений
	SetCurselsChanged();
}


void CChooseAssembleDlg::OnCbnSelchangecCombo()
{
	// TODO: добавьте свой код обработчика уведомлений
	SetCurselsChanged();
}
void CChooseAssembleDlg::OnCbnSelchangelCombo()
{
	SetCurselsChanged();
}

void CChooseAssembleDlg::OnSelchanged1Combo()
{
	// TODO: добавьте свой код обработчика уведомлений
	SetCurselsChanged();
}


void CChooseAssembleDlg::SetCurselsChanged()
{
	if (m_treeFromGetTree != m_hAssemble)
	{
		CString C_D,C_D1,C_b1,C_c1,C_d1,C_c,C_f,C_r,C_L,C_l;
		double D,D1,b1,d1,c1,c,f,r,L,l;
		if (m_treeFromGetTree == m_hRing)
		{
			m_DCOMBO.GetLBText(m_DCOMBO.GetCurSel(),C_D);
			D = CStringTODouble(C_D);

			m_D1COMBO.GetLBText(m_D1COMBO.GetCurSel(), C_D1);
			D1 = CStringTODouble(C_D1);

			m_b1COMBO.GetLBText(m_b1COMBO.GetCurSel(), C_b1);
			b1 = CStringTODouble(C_b1);


			for (int i = 0; i < Assembles::GetAllAssembles().size();i++)
			{
				double _b1 = Assembles::GetAllAssembles()[i].Getb1();
				double _D1 = Assembles::GetAllAssembles()[i].GetD1();
				double _D = Assembles::GetAllAssembles()[i].GetD();
				if (_b1 == b1 && _D1 == D1 && _D == D)
				{
					ChangeNM(i);
					break;
				}
				else
				{
					m_NMReadonlyEDIT.SetWindowTextW(L"");
					for (int i = 0; i < m_holeCOMBO.GetCount();i++)
					{
						m_holeCOMBO.DeleteString(i);
					}
					/*m_holeCOMBO.Clear();*/
				}
			}
		}
		else if (m_treeFromGetTree == m_hScrew)
		{
			m_DCOMBO.GetLBText(m_DCOMBO.GetCurSel(), C_D);
			D = CStringTODouble(C_D);

			m_D1COMBO.GetLBText(m_D1COMBO.GetCurSel(), C_D1);
			D1 = CStringTODouble(C_D1);

			m_b1COMBO.GetLBText(m_b1COMBO.GetCurSel(), C_b1);
			b1 = CStringTODouble(C_b1);

			m_d1COMBO.GetLBText(m_d1COMBO.GetCurSel(), C_d1);
			d1 = CStringTODouble(C_d1);

			m_c1COMBO.GetLBText(m_c1COMBO.GetCurSel(), C_c1);
			c1 = CStringTODouble(C_c1);

			for (int i = 0; i < Assembles::GetAllAssembles().size();i++)
			{
				double _b1 = Assembles::GetAllAssembles()[i].Getb1();
				double _D1 = Assembles::GetAllAssembles()[i].GetD1();
				double _D = Assembles::GetAllAssembles()[i].GetD();
				double _c1 = Assembles::GetAllAssembles()[i].Getc1();
				double _d1 = Assembles::GetAllAssembles()[i].Getd1();
				if (_b1 == b1 && _D1 == D1 && _D == D && _c1 == c1 && _d1 == d1)
				{
					ChangeNM(i);
					break;
				}
				else
				{
					m_NMReadonlyEDIT.SetWindowTextW(L"");
					for (int i = 0; i < m_holeCOMBO.GetCount();i++)
					{
						m_holeCOMBO.DeleteString(i);
					}
				}
			}
		}
		else if (m_treeFromGetTree == m_hCollar)
		{
			m_DCOMBO.GetLBText(m_DCOMBO.GetCurSel(), C_D);
			D = CStringTODouble(C_D);

			m_D1COMBO.GetLBText(m_D1COMBO.GetCurSel(), C_D1);
			D1 = CStringTODouble(C_D1);

			m_b1COMBO.GetLBText(m_b1COMBO.GetCurSel(), C_b1);
			b1 = CStringTODouble(C_b1);

			m_d1COMBO.GetLBText(m_d1COMBO.GetCurSel(), C_d1);
			d1 = CStringTODouble(C_d1);

			m_c1COMBO.GetLBText(m_c1COMBO.GetCurSel(), C_c1);
			c1 = CStringTODouble(C_c1);

			m_cCOMBO.GetLBText(m_cCOMBO.GetCurSel(), C_c);
			c = CStringTODouble(C_c);

			m_fCOMBO.GetLBText(m_fCOMBO.GetCurSel(), C_f);
			f = CStringTODouble(C_f);

			m_rCOMBO.GetLBText(m_rCOMBO.GetCurSel(), C_r);
			r= CStringTODouble(C_r);

			m_lCOMBO.GetLBText(m_lCOMBO.GetCurSel(), C_l);
			l = CStringTODouble(C_l);

			m_LCOMBO.GetLBText(m_LCOMBO.GetCurSel(), C_L);
			L = CStringTODouble(C_L);

			for (int i = 0; i < Assembles::GetAllAssembles().size();i++)
			{

				double _b1 = Assembles::GetAllAssembles()[i].Getb1();
				double _D1 = Assembles::GetAllAssembles()[i].GetD1();
				double _D = Assembles::GetAllAssembles()[i].GetD();
				double _c1 = Assembles::GetAllAssembles()[i].Getc1();
				double _d1 = Assembles::GetAllAssembles()[i].Getd1();
				double _c = Assembles::GetAllAssembles()[i].Getc();
				double _r = Assembles::GetAllAssembles()[i].Getr();
				double _f = Assembles::GetAllAssembles()[i].Getf();
				double _L = Assembles::GetAllAssembles()[i].GetL();
				double _l = Assembles::GetAllAssembles()[i].Getl();

				if (_b1 == b1 && _D1 == D1 && _D == D && _c1 == c1 && _d1 == d1 && c == _c && r == _r && f == _f && _L == L && _l == l)
				{
					ChangeNM(i);
					break;
				}
				else
				{
					m_NMReadonlyEDIT.SetWindowTextW(L"");
					for (int i = 0; i < m_holeCOMBO.GetCount();i++)
					{
						m_holeCOMBO.DeleteString(i);
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
	if (m_NMReadonlyEDIT.GetWindowTextLengthW() == 0 && m_treeFromGetTree != m_hAssemble)
	{
		if (MessageBox(L"Выбранные вами параметры не подходят ни одному крутящему моменту.\nЕсли вы закроете данное окно, выставленные вами параметры будут сброшены.", L"Вы уверены, что хотите закрыть данное окно?", MB_OKCANCEL) != IDOK)
		{
			return;
		}
	}
	CDialogEx::OnOK();
}


void CChooseAssembleDlg::OnBnClickedCancel()
{
	m_pAssembler->m_gost = m_oldGost;
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}



