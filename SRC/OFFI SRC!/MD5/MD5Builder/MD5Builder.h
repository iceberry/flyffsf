// MD5Builder.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CMD5BuilderApp:
// �йش����ʵ�֣������ MD5Builder.cpp
//

class CMD5BuilderApp : public CWinApp
{
public:
	CMD5BuilderApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMD5BuilderApp theApp;
