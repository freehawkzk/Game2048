
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// Game2048.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


float g_fBordLineWidth = 4.0f;//��Ϸ����߿��߿�
float g_fGapWidth = 4.0f;//��֮��ļ�����
Gdiplus::Color g_colorBordLine(255,0,0);//��Ϸ��ԭ�߿���ɫ
Gdiplus::Color g_colorGameBkg(125,125,125);//��Ϸ���򱳾���ɫ
Gdiplus::Color g_colorBlocks[11];//2����ɫ
Gdiplus::Color g_colorText(255,255,255);//������ɫ
int g_nBlockNumX = 4;//��Ϸ������X����ķ�����
int g_nBlockNumY = 4;//��Ϸ������Y����ķ�����
vv g_vvData;//������Ϸ�����и���ĵ�ǰֵ
colorIndexMap g_colorMap;//���ݷ���ֵȷ����ɫֵ
indexStringMap g_indexStringMap;//����ֵת��Ϊ�ַ���