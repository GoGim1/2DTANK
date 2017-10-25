#pragma once

#include <stdlib.h>
#include"setting.h"

HBITMAP		g_hBroad = (HBITMAP)LoadImage(NULL, L"pic//broad.bmp", IMAGE_BITMAP, WINDOW_WIDTH, 1.5 * WINDOW_HEIGHT/19, LR_LOADFROMFILE);

void PaintBroad(int point1,int point2,int gametime)
{
	SelectObject(g_bufdc, g_hBroad);
	BitBlt(g_mdc, 0, WINDOW_HEIGHT, WINDOW_WIDTH, 1.5 * WINDOW_HEIGHT / 19, g_bufdc, 0, 0, SRCCOPY);

	HFONT hFont = CreateFont(WINDOW_WIDTH/40, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"Î¢ÈíÑÅºÚ");
	SelectObject(g_mdc, hFont);
	SetBkMode(g_mdc, TRANSPARENT);
	SetTextColor(g_mdc, RGB(235,174,59));
	wchar_t Point1[] = L"000";
	wchar_t Point2[] = L"000";
	_itow_s(point1, Point1, 10);
	_itow_s(point2, Point2, 10);
	TextOut(g_mdc, 1.05*WINDOW_WIDTH/15, WINDOW_HEIGHT+ 1.4*WINDOW_HEIGHT / 50, Point1, wcslen(Point1));
	TextOut(g_mdc, WINDOW_WIDTH - 1.22*WINDOW_WIDTH / 15, WINDOW_HEIGHT + 1.4*WINDOW_HEIGHT / 50, Point2, wcslen(Point2));

	DeleteObject(hFont);

}

void PaintTime(int gametime, int  tnow, int tpre)
{		
		HFONT hFont = CreateFont(64, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"Î¢ÈíÑÅºÚ");
		wchar_t GameTime[] = L"000";
		_itow_s(gametime, GameTime, 10);
		SetTextColor(g_mdc, RGB(0, 0, 0));
		TextOut(g_mdc, 7.35*WINDOW_WIDTH / 15,51*WINDOW_HEIGHT / 50, GameTime, wcslen(GameTime));
}
