
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持



#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")

#include <vector>
#include <map>
extern float g_fBordLineWidth;//游戏区域边框线宽
extern float g_fGapWidth;//块之间的间隔宽度
extern Gdiplus::Color g_colorBordLine;//游戏屈原边框颜色
extern Gdiplus::Color g_colorGameBkg;//游戏区域背景颜色
extern Gdiplus::Color g_colorBlocks[11];//2块颜色
extern Gdiplus::Color g_colorText;//文字颜色
extern int g_nBlockNumX;//游戏区域中X方向的方块数
extern int g_nBlockNumY;//游戏区域中Y方向的方块数

typedef std::vector<std::vector<int> > vv;
extern vv g_vvData;//保存游戏区域中各块的当前值

typedef std::map<int, Gdiplus::Color> colorIndexMap;
extern colorIndexMap g_colorMap;//根据分数值确定颜色值

typedef std::map<int, WCHAR*> indexStringMap;
extern indexStringMap g_indexStringMap;//将分值转换为字符串
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


