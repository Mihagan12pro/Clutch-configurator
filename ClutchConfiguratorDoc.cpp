
// ClutchConfiguratorDoc.cpp: реализация класса CClutchConfiguratorDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "ClutchConfigurator.h"
#endif

#include "ClutchConfiguratorDoc.h"
#include"CAssembleTree.h"
#include <propkey.h>
#include"CClutchAssembler.h"
#include"ClutchConfiguratorDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CClutchConfiguratorDoc

IMPLEMENT_DYNCREATE(CClutchConfiguratorDoc, CDocument)

BEGIN_MESSAGE_MAP(CClutchConfiguratorDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CClutchConfiguratorDoc

CClutchConfiguratorDoc::CClutchConfiguratorDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CClutchConfiguratorDoc::~CClutchConfiguratorDoc()
{
}

BOOL CClutchConfiguratorDoc::OnNewDocument()
{
	this->SetTitle(L"API Компаса 3Д");

	CClutchAssembler::SetFolderName("C:\\Сборка втулочной муфты");
	CClutchAssembler::SetCollarName("Втулка.m3d");
	CClutchAssembler::SetRingName("Кольцо.m3d");
	CClutchAssembler::SetScrewName("Винт.m3d");

	CAssemblesCollection::InitializeAssembles();

	if (!CDocument::OnNewDocument())
		return FALSE;
	m_pAssembleTree -> FillTree();
	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CClutchConfiguratorDoc

void CClutchConfiguratorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CClutchConfiguratorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CClutchConfiguratorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CClutchConfiguratorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CClutchConfiguratorDoc

#ifdef _DEBUG
void CClutchConfiguratorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClutchConfiguratorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG


// Команды CClutchConfiguratorDoc
