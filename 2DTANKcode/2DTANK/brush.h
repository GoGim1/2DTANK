#pragma once

#include"setting.h"


class Brush
{
public:
	int x, y;
	void SetXY(int a, int b)
	{
		x = a * WINDOW_WIDTH / 19;
		y = b * WINDOW_HEIGHT / 15;
	}
	bool IfBrush(int a, int b)
	{
		if (a == x&&y == b)
		{
			return true;
		}
		return false;
	}
	~Brush()
	{
	}
};

HBITMAP		g_hBrush = (HBITMAP)LoadImage(NULL, L"pic//brush.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
Brush		brush[BRUSH_NUMBER];

void SetBrush()
{

	for (int i = 0; i < 3; i++)
	{
		brush[i].SetXY(i + 1, 1);
	}
	for (int i = 3; i < 6; i++)
	{
		brush[i].SetXY(i + 12, 13);
	}
	brush[6].SetXY(1, 2); brush[7].SetXY(17, 12);
	int k = 8;
	for (int i = 6; i < 9; i++)
	{
		for (int j = 5; j < 14; j++, k++)
		{
			brush[k].SetXY(j, i);
		}
	}
}

void PaintBrush()
{
	for (int i = 0; i < 35; i++)
	{
		SelectObject(g_bufdc, g_hBrush);
		TransparentBlt(g_mdc, brush[i].x, brush[i].y, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, g_bufdc, 0, 0, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, RGB(0, 0, 0));
	}
}