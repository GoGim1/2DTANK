#pragma once

#define WINDOW_WIDTH	760					//为窗口宽度定义的宏，以方便在此处修改窗口宽度
#define WINDOW_HEIGHT	600	 				//为窗口高度定义的宏，以方便在此处修改窗口高度
#define WINDOW_TITLE	L"2D TANK GAME "	//为窗口标题定义的宏
#define STONE_NUMBER	102					//石头数目	
#define BRUSH_NUMBER	35					//树丛树木
#define BULLET_NUMBER	30					//屏幕内能出现同一辆坦克的子弹最大数目
#define HARDLEVEL		150					//越小AI速度越大
#define GAME_TIME		15
#define BULLET_SPEED	1					//越小子弹速度越慢

#include <windows.h>
#include <tchar.h>							//使用swprintf_s函数所需的头文件

HDC		g_hdc = NULL, g_mdc = NULL, g_bufdc = NULL;      //全局设备环境句柄与两个全局内存DC句柄
