
// TestPersonNumbDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestPersonNumbDemoApp:
// �йش����ʵ�֣������ TestPersonNumbDemo.cpp
//

class CTestPersonNumbDemoApp : public CWinApp
{
public:
	CTestPersonNumbDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestPersonNumbDemoApp theApp;