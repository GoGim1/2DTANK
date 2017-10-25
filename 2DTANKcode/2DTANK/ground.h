#pragma once
#include"setting.h"

HBITMAP		g_hBackGround = (HBITMAP)LoadImage(NULL, L"pic//map.bmp", IMAGE_BITMAP, WINDOW_WIDTH, WINDOW_HEIGHT, LR_LOADFROMFILE);

void PaintGround()
{
	SelectObject(g_bufdc, g_hBackGround);
	BitBlt(g_mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_bufdc, 0, 0, SRCCOPY);
}