
// stdafx.cpp : 只包括标准包含文件的源文件
// Game2048.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


float g_fBordLineWidth = 4.0f;//游戏区域边框线宽
float g_fGapWidth = 4.0f;//块之间的间隔宽度
Gdiplus::Color g_colorBordLine(255,0,0);//游戏屈原边框颜色
Gdiplus::Color g_colorGameBkg(125,125,125);//游戏区域背景颜色
Gdiplus::Color g_colorBlocks[11];//2块颜色
Gdiplus::Color g_colorText(255,255,255);//文字颜色
int g_nBlockNumX = 4;//游戏区域中X方向的方块数
int g_nBlockNumY = 4;//游戏区域中Y方向的方块数
vv g_vvData;//保存游戏区域中各块的当前值
colorIndexMap g_colorMap;//根据分数值确定颜色值
indexStringMap g_indexStringMap;//将分值转换为字符串