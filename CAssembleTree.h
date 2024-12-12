#pragma once

#include"afxcview.h"
// Просмотр CAssembleTree
class CClutchConfiguratorDoc;
class CAssembleTree : public CTreeView
{
	DECLARE_DYNCREATE(CAssembleTree)

protected:
	HTREEITEM m_hAssemble, m_hCollar, m_hRing, m_hScrew;
	CAssembleTree();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CAssembleTree();

public:
	void FillTree();
	CClutchConfiguratorDoc* m_pDoc;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


