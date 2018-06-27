
// Game2048.cpp : 定义应用程序的类行为。
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


// CGame2048App 构造

CGame2048App::CGame2048App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CGame2048App 对象

CGame2048App theApp;


// CGame2048App 初始化

BOOL CGame2048App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

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
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



int CGame2048App::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return CWinApp::ExitInstance();
}
