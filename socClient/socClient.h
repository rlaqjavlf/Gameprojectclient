
// socClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CsocClientApp:
// �� Ŭ������ ������ ���ؼ��� socClient.cpp�� �����Ͻʽÿ�.
//

class CsocClientApp : public CWinApp
{
public:
	CsocClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CsocClientApp theApp;