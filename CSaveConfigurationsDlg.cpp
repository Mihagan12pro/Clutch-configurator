// CSaveConfigurationsDlg.cpp: файл реализации
//

#include "pch.h"
#include "ClutchConfigurator.h"
#include "afxdialogex.h"
#include "CSaveConfigurationsDlg.h"


// Диалоговое окно CSaveConfigurationsDlg

IMPLEMENT_DYNAMIC(CSaveConfigurationsDlg, CDialogEx)

CSaveConfigurationsDlg::CSaveConfigurationsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PATHS_EDITOR, pParent)
{

}

CSaveConfigurationsDlg::~CSaveConfigurationsDlg()
{
}

void CSaveConfigurationsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveConfigurationsDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений CSaveConfigurationsDlg


BOOL CSaveConfigurationsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// TODO:  Добавить дополнительную инициализацию

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
