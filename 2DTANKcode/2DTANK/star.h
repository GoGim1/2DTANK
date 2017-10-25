#pragma once

#include<time.h>
#include"setting.h"
#include"block.h"


class Star
{
public:
	int			x, y=0;
	int			i;
	bool		 set,ifblock;
	HBITMAP		g_hStar = (HBITMAP)LoadImage(NULL, L"pic//star.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);

	void SetStar(int playertankx, int playertanky, int  aitankx, int aitanky);
	void PaintStar();
	Star();
	~Star();

private:

};

Star::Star()
{
}

Star::~Star()
{
	DeleteObject(g_hStar);
}

void Star::SetStar(int playertankx, int playertanky,int  aitankx, int aitanky)
{	
	set = false;
	x = (playertankx + aitankx) / (WINDOW_WIDTH / 19) / 2* (WINDOW_WIDTH / 19);
	y =(playertanky + aitanky) / (WINDOW_HEIGHT / 15) / 2* (WINDOW_HEIGHT / 15);
	if ((abs(playertankx-x)<6* (WINDOW_WIDTH / 19) && abs(playertanky - y)<6 * (WINDOW_HEIGHT / 15))|| (abs(aitanky - y)<6 * (WINDOW_HEIGHT / 15) && abs(aitankx - x)<6* (WINDOW_WIDTH / 19)))
	{
		x = (rand() % 19)* (WINDOW_WIDTH / 19);
		y = (rand() % 15)* (WINDOW_HEIGHT / 15);
	}
	for (; set==false;)
	{
		
		ifblock = false;

		for (i = 0; i < STONE_NUMBER; i++)
		{
			if (block[i].x==x&&block[i].y==y)
			{
				ifblock = true;
				break;
			}
		}
		if (ifblock==false)
		{
			set = true;
			break;
		}	
		x = (rand() % 19)* (WINDOW_WIDTH / 19);
		y = (rand() % 15)* (WINDOW_HEIGHT / 15);

	}

}

void Star::PaintStar()
{

	SelectObject(g_bufdc, g_hStar);
	TransparentBlt(g_mdc, x, y, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, g_bufdc, 0, 0, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, RGB(0, 0, 0));
}

Star star;
