
// ExtensionChange.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// メイン シンボル


// CExtensionChangeApp:
// このクラスの実装については、ExtensionChange.cpp を参照してください
//

class CExtensionChangeApp : public CWinApp
{
public:
	CExtensionChangeApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CExtensionChangeApp theApp;
