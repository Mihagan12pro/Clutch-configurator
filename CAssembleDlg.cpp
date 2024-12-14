// CAssembleDlg.cpp: файл реализации
//

#include "pch.h"
#include "ClutchConfigurator.h"
#include "afxdialogex.h"
#include "CAssembleDlg.h"


// Диалоговое окно CAssembleDlg

IMPLEMENT_DYNAMIC(CAssembleDlg, CDialogEx)

CAssembleDlg::CAssembleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AssembleDlg, pParent)
{

}

CAssembleDlg::~CAssembleDlg()
{
}

void CAssembleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_save_assemble_EDIT, m_saveAssembleVALUE);
}


BEGIN_MESSAGE_MAP(CAssembleDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений CAssembleDlg


BOOL CAssembleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	m_saveAssembleVALUE = L"C:\\MyAssemble";
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
