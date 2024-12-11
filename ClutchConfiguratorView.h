﻿
// ClutchConfiguratorView.h: интерфейс класса CClutchConfiguratorView
//

#pragma once


class CClutchConfiguratorView : public CFormView
{
protected: // создать только из сериализации
	CClutchConfiguratorView() noexcept;
	DECLARE_DYNCREATE(CClutchConfiguratorView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_CLUTCHCONFIGURATOR_FORM };
#endif

// Атрибуты
public:
	CClutchConfiguratorDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CClutchConfiguratorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
	CStatic m_sketchPicture;
};

#ifndef _DEBUG  // версия отладки в ClutchConfiguratorView.cpp
inline CClutchConfiguratorDoc* CClutchConfiguratorView::GetDocument() const
   { return reinterpret_cast<CClutchConfiguratorDoc*>(m_pDocument); }
#endif

