// CChooseAssembleDlg.cpp: файл реализации
//

#include "pch.h"
#include "ClutchConfigurator.h"
#include "afxdialogex.h"
#include "CChooseAssembleDlg.h"
#include "CClutchAssembler.h"
#include "MainFrm.h"
#include "CClutchAssembler.h"

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


//void CChooseAssembleDlg::GetTreeItem(HTREEITEM &item)
//{
//	if (item == m_hAssemble)
//	{
//		int a = 1;
//	}
//	else if (item == m_hCollar)
//	{
//
//	}
//	else if (item == m_hRing)
//	{
//
//	}
//	else if (item == m_hScrew)
//	{
//
//	}
//}

void CChooseAssembleDlg::GetTreeItem(HTREEITEM item)
{
	m_treeFromGetTree = item;
	//SetWindowText(_T("Мое новое название"));
	if (item == m_hAssemble)
	{
		//SetWindowText(L"Сборка втулочной муфты");
		//SetWindowText(L"Мое новое название");
	}
	else if (item == m_hRing)
	{
		//SetWindowText(L"Кольцо");
	}
	else if (item == m_hCollar)
	{
		//SetWindowText(L"Втулка");
	}
	else if (item == m_hScrew)
	{
		//SetWindowText(L"Винт");
	}
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
	
	if (m_treeFromGetTree == m_hAssemble)
	{
		SetWindowText(L"Сборка втулочной муфты");
		//SetWindowText(L"Мое новое название");
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
