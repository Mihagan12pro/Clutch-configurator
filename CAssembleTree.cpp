// CAssembleTree.cpp: файл реализации
//

#include "pch.h"
#include "ClutchConfigurator.h"
#include "CAssembleTree.h"
#include"CChooseAssembleDlg.h"

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

	wchar_t* pSketch = nullptr;
	if (item == m_hAssemble)
	{

	}
	else if (item == m_hCollar)
	{

	}
	else if (item == m_hRing)
	{
		 pSketch = L"Sketches\\Ring.bmp";
		
	}
	else if (item == m_hScrew)
	{
		pSketch = L"Sketches\\Screw.bmp";
	}



	if (pSketch != nullptr)
	{
		m_pView->SetSketchImage(pSketch);
	}

	
}


void CAssembleTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeView::OnLButtonDblClk(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();
	HTREEITEM item = tree.GetSelectedItem();

	if (item != NULL)
	{
		CChooseAssembleDlg::GetTreeItem(item);
	}
	
}
