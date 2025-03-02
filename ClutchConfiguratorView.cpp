﻿
// ClutchConfiguratorView.cpp: реализация класса CClutchConfiguratorView
//

#include "pch.h"
#include <atlimage.h> 
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "ClutchConfigurator.h"
#endif

#include "ClutchConfiguratorDoc.h"
#include "ClutchConfiguratorView.h"
#include"CSaveConfigurationsDlg.h"
#include"MainFrm.h"
#include"CClutchAssembler.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClutchConfiguratorView

IMPLEMENT_DYNCREATE(CClutchConfiguratorView, CFormView)

BEGIN_MESSAGE_MAP(CClutchConfiguratorView, CFormView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	ON_COMMAND(ID_whereSaveMenu, &CClutchConfiguratorView::OnWhereSaveMenu)
	ON_STN_CLICKED(IDC_PICTURE_STATIC, &CClutchConfiguratorView::OnStnClickedPictureStatic)
	ON_COMMAND(ID_BUILD_ASSEMBLY, &CClutchConfiguratorView::OnBuildAssembly)
END_MESSAGE_MAP()

// Создание или уничтожение CClutchConfiguratorView

CClutchConfiguratorView::CClutchConfiguratorView() noexcept
	: CFormView(IDD_CLUTCHCONFIGURATOR_FORM)
{
	// TODO: добавьте код создания

}

CClutchConfiguratorView::~CClutchConfiguratorView()
{
}

void CClutchConfiguratorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_Sketch_PICTURE, m_sketchPicture);
	//DDX_Control(pDX, IDC_PICTURE_STATIC, m_stetchImage);
	DDX_Control(pDX, IDC_PICTURE_STATIC, m_sketchImage);
}

BOOL CClutchConfiguratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	
	return CFormView::PreCreateWindow(cs);
}

void CClutchConfiguratorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// Печать CClutchConfiguratorView

BOOL CClutchConfiguratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CClutchConfiguratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CClutchConfiguratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CClutchConfiguratorView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте свой код печати
}


// Диагностика CClutchConfiguratorView

#ifdef _DEBUG
void CClutchConfiguratorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CClutchConfiguratorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CClutchConfiguratorDoc* CClutchConfiguratorView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClutchConfiguratorDoc)));
	return (CClutchConfiguratorDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CClutchConfiguratorView


void CClutchConfiguratorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	
	if(&pFrame->GetAssembler() != nullptr)
	{
		Assembler assembler = pFrame->GetAssembler();
		assembler.BuildAssemble();
	}
	CFormView::OnLButtonDown(nFlags, point);
}


void CClutchConfiguratorView::OnClose()
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CFormView::OnClose();
}


void CClutchConfiguratorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
	CFormView::OnRButtonDown(nFlags, point);
}


int CClutchConfiguratorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}


void CClutchConfiguratorView::OnWhereSaveMenu()
{
	CSaveConfigurationsDlg dlg;

	if (dlg.DoModal() == IDOK)
	{

	}
	// TODO: добавьте свой код обработчика команд
}
void CClutchConfiguratorView::SetSketchImage(int bitmapID)
{
	bool bFlag = true;
	
	m_sketchImage.SetBitmap
	(
		LoadBitmap
		(
			GetModuleHandle(NULL),
			MAKEINTRESOURCE(bFlag ? bitmapID : bitmapID)
		)
	);
	bFlag = !bFlag;
}


void CClutchConfiguratorView::OnStnClickedPictureStatic()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CClutchConfiguratorView::OnBuildAssembly()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	if (&pFrame->GetAssembler() != nullptr)
	{
		Assembler assembler = pFrame->GetAssembler();
		assembler.BuildAssemble();
	}
}
