﻿
// MainFrm.h: интерфейс класса CMainFrame
//

#pragma once
#include"CClutchAssembler.h"
#include "CChooseAssembleDlg.h"
#include"CAssembleTree.h"
//class CClutchAssembler;
class CClutchConfiguratorView;
#include"Other.h"
class CMainFrame : public CFrameWnd
{
	
	protected: // создать только из сериализации
		CMainFrame() noexcept;
		DECLARE_DYNCREATE(CMainFrame)

	// Атрибуты
	public:

	// Операции
	public:

	// Переопределение
	public:
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Реализация
	public:
		//CClutchAssembler GetAssembler();
		virtual ~CMainFrame();
	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif

	protected:  // встроенные члены панели элементов управления
		CToolBar          m_wndToolBar;
		CStatusBar        m_wndStatusBar;
		CSplitterWnd      m_wndSplitter;

	// Созданные функции схемы сообщений
	protected:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		DECLARE_MESSAGE_MAP()

		virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	private:
		CClutchAssembler* m_pAssembler;
	private:
		friend class CChooseAssembleDlg;
		friend class CAssembleTree;
		/*friend class CClutchConfiguratorView;*/
	public:
		Assembler GetAssembler();
};


