// CAssembleTree.cpp: файл реализации
//

#include "pch.h"
#include "ClutchConfigurator.h"
#include "CAssembleTree.h"


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
}