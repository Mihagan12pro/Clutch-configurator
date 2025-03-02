﻿// CAssembleTree.cpp: файл реализации
//

#include "pch.h"
#include "ClutchConfigurator.h"
#include "CAssembleTree.h"
#include"CChooseAssembleDlg.h"
#include"MainFrm.h"
// CAssembleTree

IMPLEMENT_DYNCREATE(CAssembleTree, CTreeView)

CAssembleTree::CAssembleTree()
{

}

CAssembleTree::~CAssembleTree()
{
}

BEGIN_MESSAGE_MAP(CAssembleTree, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_CLICK, &CAssembleTree::OnNMClick)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_BUILD_ASSEMBLY, &CAssembleTree::OnBuildAssembly)
END_MESSAGE_MAP()


// Диагностика CAssembleTree

#ifdef _DEBUG
void CAssembleTree::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CAssembleTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CAssembleTree


int CAssembleTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}
void CAssembleTree::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();

	tree.DeleteAllItems();

	m_hAssemble = tree.InsertItem(L"Сборка втулочной муфты", -1, -1, NULL, TVI_FIRST);

	m_hCollar = tree.InsertItem(L"Втулка", -1, -1, m_hAssemble, TVI_FIRST);
	m_hRing = tree.InsertItem(L"Кольцо", -1, -1, m_hAssemble, TVI_FIRST);
	m_hScrew = tree.InsertItem(L"Винт", -1, -1, m_hAssemble, TVI_FIRST);

	tree.Expand(m_hAssemble, TVE_EXPAND);

	CChooseAssembleDlg::SetHTREEITEMs(m_hAssemble,m_hCollar,m_hRing,m_hScrew);
}

void CAssembleTree::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;
}


void CAssembleTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTreeView::OnLButtonDown(nFlags, point);
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CTreeCtrl& tree = GetTreeCtrl();
	HTREEITEM item = tree.GetSelectedItem();

	int bitmapId=0;
	
	
	if (item == m_hCollar)
	{
		bitmapId = IDB_COLLAR_BITMAP;
	}
	else if (item == m_hRing)
	{
		bitmapId = IDB_RING_BITMAP;
	}
	else if (item == m_hScrew)
	{
		bitmapId = IDB_SCREW_BITMAP;
	}

	else
	{
		bitmapId = IDB_ASSEMBLE_BITMAP;
	}
		m_pView->SetSketchImage(bitmapId);
}


void CAssembleTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeView::OnLButtonDblClk(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();
	HTREEITEM item = tree.GetSelectedItem();

	if (item != NULL)
	{
		CChooseAssembleDlg dlg;
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	

		dlg.SetExternalItems(item,*pFrame->m_pAssembler);
		

		if (dlg.DoModal() == IDOK)
		{
			pFrame->m_pAssembler = new Assembler(dlg.GetAssemble(),dlg.GetGost());
		}
	}
	
}


void CAssembleTree::OnBuildAssembly()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	if (&pFrame->GetAssembler() != nullptr)
	{
		Assembler assembler= pFrame->GetAssembler();
		assembler.BuildAssemble();
	}
}
