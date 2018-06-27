
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��



#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")

#include <vector>
#include <map>
extern float g_fBordLineWidth;//��Ϸ����߿��߿�
extern float g_fGapWidth;//��֮��ļ�����
extern Gdiplus::Color g_colorBordLine;//��Ϸ��ԭ�߿���ɫ
extern Gdiplus::Color g_colorGameBkg;//��Ϸ���򱳾���ɫ
extern Gdiplus::Color g_colorBlocks[11];//2����ɫ
extern Gdiplus::Color g_colorText;//������ɫ
extern int g_nBlockNumX;//��Ϸ������X����ķ�����
extern int g_nBlockNumY;//��Ϸ������Y����ķ�����

typedef std::vector<std::vector<int> > vv;
extern vv g_vvData;//������Ϸ�����и���ĵ�ǰֵ

typedef std::map<int, Gdiplus::Color> colorIndexMap;
extern colorIndexMap g_colorMap;//���ݷ���ֵȷ����ɫֵ

typedef std::map<int, WCHAR*> indexStringMap;
extern indexStringMap g_indexStringMap;//����ֵת��Ϊ�ַ���
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


