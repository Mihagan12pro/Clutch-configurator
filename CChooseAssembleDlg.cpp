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
END_MESSAGE_MAP()


// Обработчики сообщений CChooseAssembleDlg


BOOL CChooseAssembleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_assembler = ((CMainFrame*)AfxGetMainWnd())->m_pAssembler;
	m_AssemblesTable.SetExtendedStyle(LVS_EX_GRIDLINES);
	if (m_treeFromGetTree == m_hAssemble)
	{
		SetWindowText(L"Сборка втулочной муфты");
		/*m_AssemblesTable.ShowWindow(SW_SHOW);*/
		m_AssemblesTable.InsertColumn(0,L"Мкр", LVCFMT_LEFT,65);
		m_AssemblesTable.InsertColumn(1, L"D", LVCFMT_LEFT, 30);
		m_AssemblesTable.InsertColumn(2, L"D1", LVCFMT_LEFT, 30);
		m_AssemblesTable.InsertColumn(3, L"b1", LVCFMT_LEFT, 30);
		m_AssemblesTable.InsertColumn(4, L"d1", LVCFMT_LEFT, 30);
		m_AssemblesTable.InsertColumn(5, L"L", LVCFMT_LEFT, 30);
		m_AssemblesTable.InsertColumn(6, L"l", LVCFMT_LEFT, 30);
		m_AssemblesTable.InsertColumn(7, L"r", LVCFMT_LEFT, 30);
		m_AssemblesTable.InsertColumn(8, L"f", LVCFMT_LEFT, 30);
		m_AssemblesTable.InsertColumn(9, L"c", LVCFMT_LEFT, 30);
		m_AssemblesTable.InsertColumn(10, L"c1", LVCFMT_LEFT, 30);
	/*	for (int i = 0; i < Assembles::GetAllAssembled().size();i++)
		{
			int item = m_AssemblesTable.InsertItem(i, Assembles::GetAllAssembled()[i].GetNM());
		}
		*/
	}
	else if (m_treeFromGetTree == m_hRing)
	{
		SetWindowText(L"Кольцо");
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

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
CString CChooseAssembleDlg::DoubleToCString(double number)
{
	CString strNumber;

	strNumber.Format(L"%f",number);

	return strNumber;
}