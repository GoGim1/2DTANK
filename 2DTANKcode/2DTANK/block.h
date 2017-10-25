#pragma once

#include"setting.h"


class Block
{
public:
	int x, y;
	void SetXY(int a, int b);
	bool IfBlock(int a, int b, int dire);
	Block();
	~Block();
};

Block::Block()
{
}

Block::~Block()
{
}

bool Block::IfBlock(int a, int b, int dire)
{
	switch (dire)
	{
	case 0:
		if ((a == x) && (b == (y + (WINDOW_HEIGHT / 15))))
		{
			return true;
		}
		break;
	case 1:
		if (a == x&&b == y - (WINDOW_HEIGHT / 15))
		{
			return true;
		}
		break;
	case 2:
		if (a == x + (WINDOW_WIDTH / 19) && b == y)
		{
			return true;
		}
		break;
	case 3:
		if (a == x - (WINDOW_WIDTH / 19) && b == y)
		{
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

void Block::SetXY(int a, int b)
{
	x = a * WINDOW_WIDTH / 19;
	y = b * WINDOW_HEIGHT / 15;
}


HBITMAP		g_hBlock = (HBITMAP)LoadImage(NULL, L"pic//block.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
Block		block[STONE_NUMBER];

void SetBlock()
{
	
	for (int i = 0; i < 19; i++)
	{
		block[i].x = i*WINDOW_WIDTH / 19;
		block[i].y = 0;
	}
	for (int i = 19; i < 32; i++)
	{
		block[i].x = 18 * WINDOW_WIDTH / 19;
		block[i].y = (i - 18)*WINDOW_HEIGHT / 15;
	}
	for (int i = 32; i < 45; i++)
	{
		block[i].x = 0;
		block[i].y = (i - 31)*WINDOW_HEIGHT / 15;
	}
	for (int i = 45; i < 64; i++)
	{
		block[i].x = (i - 45)*WINDOW_WIDTH / 19;
		block[i].y = 14 * WINDOW_HEIGHT / 15;
	}
	for (int i = 64; i < 75; i++)
	{
		block[i].SetXY(i - 61, 5);
	}
	for (int i = 75; i < 86; i++)
	{
		block[i].SetXY(i - 70, 9);
	}
	block[86].SetXY(1, 3); block[87].SetXY(2, 3); block[88].SetXY(3, 3); block[89].SetXY(17, 11); block[90].SetXY(16, 11); block[91].SetXY(15, 11);
	block[92].SetXY(3, 2); block[93].SetXY(15, 12);
	block[94].SetXY(9, 2); block[95].SetXY(9, 3); block[96].SetXY(9, 4);
	block[97].SetXY(9, 10); block[98].SetXY(9, 11); block[99].SetXY(9, 12);
	block[100].SetXY(7, 6); block[101].SetXY(11, 8);
}

void PaintBlock()
{
	for (int i = 0; i < STONE_NUMBER; i++)
	{
		SelectObject(g_bufdc, g_hBlock);
		TransparentBlt(g_mdc, block[i].x, block[i].y, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, g_bufdc, 0, 0, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, RGB(0, 0, 0));
	}

}
