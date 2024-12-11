
// ClutchConfiguratorView.cpp: реализация класса CClutchConfiguratorView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "ClutchConfigurator.h"
#endif

#include "ClutchConfiguratorDoc.h"
#include "ClutchConfiguratorView.h"

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
	DDX_Control(pDX, IDC_Sketch_PICTURE, m_sketchPicture);
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
