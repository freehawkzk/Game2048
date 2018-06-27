
// Game2048.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Game2048.h"
#include "Game2048Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGame2048App

BEGIN_MESSAGE_MAP(CGame2048App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGame2048App ����

CGame2048App::CGame2048App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CGame2048App ����

CGame2048App theApp;


// CGame2048App ��ʼ��

BOOL CGame2048App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	g_colorBlocks[0] = Gdiplus::Color(0, 255, 0);
	g_colorBlocks[1] = Gdiplus::Color(0, 125, 0);
	g_colorBlocks[2] = Gdiplus::Color(0, 0, 255);
	g_colorBlocks[3] = Gdiplus::Color(0, 0, 125);
	g_colorBlocks[4] = Gdiplus::Color(125, 0, 0);
	g_colorBlocks[5] = Gdiplus::Color(125, 255, 0);
	g_colorBlocks[6] = Gdiplus::Color(125, 125, 0);
	g_colorBlocks[7] = Gdiplus::Color(0, 255, 255);
	g_colorBlocks[8] = Gdiplus::Color(0, 255,125);
	g_colorBlocks[9] = Gdiplus::Color(0, 125, 255);
	g_colorBlocks[10] = Gdiplus::Color(0, 125,125);

	WCHAR * strs[] = { {L"2"},{L"4"} ,{ L"8" } ,{ L"16" } ,{ L"32" } ,{ L"64" } ,{ L"128" } ,{ L"256" } ,{ L"512" } ,{ L"1024" } ,{ L"2048" },{L""} };
	for (int i = 0; i < 11; i++)
	{
		g_colorMap.insert(std::pair<int,Gdiplus::Color>((int)(pow(2, i+1)), g_colorBlocks[i]));
		g_indexStringMap.insert(std::pair<int, WCHAR*>((int)(pow(2, i + 1)), strs[i]));
	}

	g_colorMap.insert(std::pair<int, Gdiplus::Color>(0, g_colorGameBkg));
	g_indexStringMap.insert(std::pair<int, WCHAR*>(0, L""));
	CGame2048Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CGame2048App::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return CWinApp::ExitInstance();
}
