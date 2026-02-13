
// IT2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CIT2App:
// Сведения о реализации этого класса: IT2.cpp
//

class CIT2App : public CWinApp
{
public:
	CIT2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CIT2App theApp;
