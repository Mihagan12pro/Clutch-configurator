
// ClutchConfigurator.h: основной файл заголовка для приложения ClutchConfigurator
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CClutchConfiguratorApp:
// Сведения о реализации этого класса: ClutchConfigurator.cpp
//

class CClutchConfiguratorApp : public CWinApp
{
public:
	CClutchConfiguratorApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CClutchConfiguratorApp theApp;
