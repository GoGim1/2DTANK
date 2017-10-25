#pragma once

#include"setting.h"
#include"bullet.h"
#include"star.h"

int route[41] = { 0 };
int step = 0;

class Tank
{
public:
	int		x, y, direction, predirection;
	int		g_bulletNum = 0;
	int		starnumber = 0;
	bool	exist=true;
	Bullet	bullet[BULLET_NUMBER];
	HBITMAP g_hTank[4] = { NULL },
			g_hBullet = (HBITMAP)LoadImage(NULL, L"pic//bullet.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
	Tank();
	~Tank();	
	void SetTank(int, int, int);
	void PaintTank( Tank* );
	void Move(WPARAM wParam,int,int);
	void Shot();
private:

};

Tank::Tank()
{

}

Tank::~Tank()
{
}

void Tank::PaintTank(Tank* Enemy)
{
	//paint bullet
	SelectObject(g_bufdc, g_hBullet);
	if (g_bulletNum != 0)
	{
		for (int i = 0; i < BULLET_NUMBER; i++)
		{
			if (bullet[i].exist)
			{
				//判断是否被树丛覆盖
				bool ifbrush = false;
				for (int j = 0; j < BRUSH_NUMBER; j++)
				{
					if (brush[j].IfBrush(bullet[i].x, bullet[i].y))
					{
						ifbrush = true;
						break;
					}
				}
				if (!ifbrush)
				{
					TransparentBlt(g_mdc, bullet[i].x, bullet[i].y, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, g_bufdc, 0, 0, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, RGB(0, 0, 0));
				}

				//判断是否被石头阻挡
				bool ifblock = false;
				for (int j = 0; j < STONE_NUMBER; j++)
				{
					if (block[j].x==bullet[i].x&&block[j].y==bullet[i].y)
					{
						ifblock = true;
						break;
					}
				}
				if (ifblock == true)
				{
					bullet[i].exist = false;
					g_bulletNum--;
					break;
				}


  				if (bullet[i].x==(Enemy->x)&&bullet[i].y==(Enemy->y))
				{
					bullet[i].exist = false;
					g_bulletNum--;
					Enemy->exist = false;
				}
				if ((Enemy->direction==0)&& (bullet[i].x == (Enemy->x))&&(bullet[i].y+WINDOW_HEIGHT/15 == (Enemy->y)))
				{
					bullet[i].exist = false;
					g_bulletNum--;
					Enemy->exist = false;
				}
				if ((Enemy->direction == 1) && (bullet[i].x == (Enemy->x)) && (bullet[i].y -WINDOW_HEIGHT / 15 == (Enemy->y)))
				{
					bullet[i].exist = false;
					g_bulletNum--;
					Enemy->exist = false;
				}
				if ((Enemy->direction == 2) && (bullet[i].x+WINDOW_WIDTH/19 == (Enemy->x)) && (bullet[i].y == (Enemy->y)))
				{
					bullet[i].exist = false;
					g_bulletNum--;
					Enemy->exist = false;
				}
				if ((Enemy->direction == 3) && (bullet[i].x - WINDOW_WIDTH / 19 == (Enemy->x)) && (bullet[i].y == (Enemy->y)))
				{
					bullet[i].exist = false;
					g_bulletNum--;
					Enemy->exist = false;
				}

				switch (bullet[i].direction)
				{
				case 0:
					bullet[i].y -= BULLET_SPEED;
					break;
				case 1:
					bullet[i].y += BULLET_SPEED;
					break;
				case 2:
					bullet[i].x -= BULLET_SPEED;
					break;
				case 3:
					bullet[i].x += BULLET_SPEED;
					break;
				default:
					break;
				}

				if (bullet[i].x<0 || bullet[i].x>WINDOW_WIDTH || bullet[i].y<0 || bullet[i].y>WINDOW_HEIGHT)
				{
					bullet[i].exist = false;
					g_bulletNum--;
				}
			}
		}
	}

	//tank
	SelectObject(g_bufdc, g_hTank[direction]);
	bool ifbrush = false;
	for (int i = 0; i < 35; i++)
	{
		if (brush[i].IfBrush(x, y))
		{
			ifbrush = true;
			break;
		}
	}
	if (!ifbrush)
	{
		TransparentBlt(g_mdc, x, y, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, g_bufdc, 0, 0, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, RGB(0, 0, 0));
	}



}

void Tank::Move(WPARAM wParam,int posx,int posy)
{
	bool ifblock = false;
	switch (wParam)
	{
	case VK_UP:				  //按下【↑】键
		predirection = direction;					  //根据按键加入人物移动的量（每次按下一次按键移动10个单位），来决定人物贴图坐标的X与Y值，接着判断坐标是否超出窗口区域，若有则进行修正
		direction = 0;
		for (int i = 0; i < STONE_NUMBER; i++)
		{
			if (block[i].IfBlock(x, y, direction))
			{
				ifblock = true;
				break;
			}
		}
		if (predirection==direction)
		{
			if (!ifblock)
			{
				y -= WINDOW_HEIGHT / 15;

				if (y < 0)
					y = 0;
			}
		}

		if (x == star.x&&y == star.y)
		{
			starnumber++;
			star.SetStar(x,y, posx, posy);
		}
		break;
	case VK_DOWN:			  //按下【↓】键
		predirection = direction;
		direction = 1;
		for (int i = 0; i < STONE_NUMBER; i++)
		{
			if (block[i].IfBlock(x, y, direction))
			{
				ifblock = true;
				break;
			}
		}
		if (predirection == direction)
		{
			if (!ifblock)
			{
				y += WINDOW_HEIGHT / 15;

				if (y > WINDOW_HEIGHT - WINDOW_HEIGHT / 15)
					y = WINDOW_HEIGHT - WINDOW_HEIGHT / 15;
			}
		}
		if (x == star.x&&y == star.y)
		{
			starnumber++;
			star.SetStar(x, y, posx, posy);
		}
		break;
	case VK_LEFT:			  //按下【←】键	
		predirection = direction;
		direction = 2;
		for (int i = 0; i < STONE_NUMBER; i++)
		{
			if (block[i].IfBlock(x, y, direction))
			{
				ifblock = true;
				break;
			}
		}
		if (predirection == direction)
		{
			if (!ifblock)
			{
				x -= WINDOW_WIDTH / 19;
				if (x < 0)
					x = 0;
			}
		}
		if (x == star.x&&y == star.y)
		{
			starnumber++;
			star.SetStar(x, y, posx, posy);
		}
		break;
	case VK_RIGHT:	//按下【→】键
		predirection = direction;
		direction = 3;
		for (int i = 0; i < STONE_NUMBER; i++)
		{
			if (block[i].IfBlock(x, y, direction))
			{
				ifblock = true;
				break;
			}
		}
		if (predirection == direction)
		{
			if (!ifblock)
			{
				x += WINDOW_WIDTH / 19;
				if (x > WINDOW_WIDTH - WINDOW_WIDTH / 19)
					x = WINDOW_WIDTH - WINDOW_WIDTH / 19;
			}
		}
		if (x == star.x&&y == star.y)
		{
			starnumber++;
			star.SetStar(x, y, posx, posy);
		}
		break;
	case VK_SPACE:
		Shot();
	}

}

void Tank::Shot()
{
	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		if (!bullet[i].exist)
		{
			bullet[i].x = x;
			bullet[i].y = y;
			bullet[i].direction = direction;
			bullet[i].exist = true;
			g_bulletNum++;
			break;
		}
	}
}

void Tank::SetTank(int posx, int posy, int dire)
{
	x = posx;
	y = posy;
	direction = dire;
}


class PlayerTank:public Tank
{
public:
	PlayerTank(int a, int b, int c);
	~PlayerTank();
private:

};

PlayerTank::PlayerTank(int a, int b, int c)
{
	g_hTank[0] = (HBITMAP)LoadImage(NULL, L"pic//tankup.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
	g_hTank[1] = (HBITMAP)LoadImage(NULL, L"pic//tankdown.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
	g_hTank[2] = (HBITMAP)LoadImage(NULL, L"pic//tankleft.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
	g_hTank[3] = (HBITMAP)LoadImage(NULL, L"pic//tankright.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
	x = a;
	y = b;
	direction = c;
}

PlayerTank::~PlayerTank()
{
	for (int i = 0; i<4; i++)
	{
		DeleteObject(g_hTank[i]);
	}
	DeleteObject(g_hBullet);
}



class AITank:public Tank
{
public:
	int HardLevel = HARDLEVEL;
	int distance[4] = { 0 };
	int distancerank[4] = { 0,1,2,3 };
	AITank(int a, int b, int c);
	~AITank();
	void AIAct(int,int,int,int);
	WPARAM AIMoveTo(int ,int);
	bool AIJudgeShot(int ,int );
	bool AIJudgeNoBlock(int ,int ,int);
private:

};

AITank::AITank(int a, int b, int c)
{
	g_hTank[0] = (HBITMAP)LoadImage(NULL, L"pic//AItankup.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
	g_hTank[1] = (HBITMAP)LoadImage(NULL, L"pic//AItankdown.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
	g_hTank[2] = (HBITMAP)LoadImage(NULL, L"pic//AItankleft.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
	g_hTank[3] = (HBITMAP)LoadImage(NULL, L"pic//AItankright.bmp", IMAGE_BITMAP, WINDOW_WIDTH / 19, WINDOW_HEIGHT / 15, LR_LOADFROMFILE);
	x = a;
	y = b;
	direction = c;
}

AITank::~AITank()
{
	for (int i = 0; i<4; i++)
	{
		DeleteObject(g_hTank[i]);
	}
	DeleteObject(g_hBullet);
}

void AITank::AIAct(int playertankx, int playertanky, int starx, int stary)
{
	WPARAM wParam;

	if (HardLevel)
	{
		HardLevel--;
		wParam = 0;
		goto stop;
	}
	HardLevel = HARDLEVEL;

	if (abs(playertankx-x)+abs(playertanky-y)<abs(starx - x) + abs(stary - y))
	{		
		if (AIJudgeShot(playertankx, playertanky))  //判断是否射击
		{
			wParam = VK_SPACE;
		}
		else
		{
			if (playertanky<3*WINDOW_HEIGHT/19&& playertankx<4*WINDOW_WIDTH/15&&y==4*WINDOW_HEIGHT/15&&x<4*WINDOW_WIDTH/19)
			{
				wParam = AIMoveTo(4 * WINDOW_WIDTH / 19, 4 * WINDOW_HEIGHT / 15);
			}
			else if (playertanky>11 * WINDOW_HEIGHT / 19 && playertankx>14 * WINDOW_WIDTH / 15 && y == 10 * WINDOW_HEIGHT / 15 && x>14 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(14 * WINDOW_WIDTH / 19, 10 * WINDOW_HEIGHT / 15);
			}
			else if (playertankx>9 * WINDOW_WIDTH / 15 && y <5 * WINDOW_HEIGHT / 15 && x<9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(9 * WINDOW_WIDTH / 19, 1 * WINDOW_HEIGHT / 15);
			}
			else if (playertanky>5 * WINDOW_WIDTH / 15 && y <5 * WINDOW_HEIGHT / 15 && x<9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(1 * WINDOW_WIDTH / 19, 5 * WINDOW_HEIGHT / 15);
			}
			else if (playertankx>9 * WINDOW_WIDTH / 15 && y >9 * WINDOW_HEIGHT / 15 && x<9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(9 * WINDOW_WIDTH / 19, 13 * WINDOW_HEIGHT / 15);
			}
			else if (playertanky<9 * WINDOW_WIDTH / 15 && y >9 * WINDOW_HEIGHT / 15 && x<9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(4 * WINDOW_WIDTH / 19, 9 * WINDOW_HEIGHT / 15);
			}
			else if (playertankx<9 * WINDOW_WIDTH / 15 && y <5 * WINDOW_HEIGHT / 15 && x>9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(9 * WINDOW_WIDTH / 19, 1 * WINDOW_HEIGHT / 15);
			}
			else if (playertanky>5 * WINDOW_WIDTH / 15 && y <5 * WINDOW_HEIGHT / 15 && x>9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(14 * WINDOW_WIDTH / 19, 5 * WINDOW_HEIGHT / 15);
			}
			else if (playertankx<9 * WINDOW_WIDTH / 15 && y >9 * WINDOW_HEIGHT / 15 && x>9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(9 * WINDOW_WIDTH / 19, 13 * WINDOW_HEIGHT / 15);
			}
			else if (playertanky<9 * WINDOW_WIDTH / 15 && y>9 * WINDOW_HEIGHT / 15 && x>9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(16 * WINDOW_WIDTH / 19, 9 * WINDOW_HEIGHT / 15);
			}
			else
			{
				wParam = AIMoveTo(playertankx, playertanky);

			}
		}
	}
	else
	{
		if (AIJudgeShot(playertankx, playertanky))  //判断是否射击
		{
			wParam = VK_SPACE;
		}
		else
		{

			if (stary < 3 * WINDOW_HEIGHT / 19 && starx < 4 * WINDOW_WIDTH / 15 && y == 4 * WINDOW_HEIGHT / 15 && x < 4 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(4 * WINDOW_WIDTH / 19, 4 * WINDOW_HEIGHT / 15);
			}
			else if (stary > 11 * WINDOW_HEIGHT / 19 && starx > 14 * WINDOW_WIDTH / 15 && y == 10 * WINDOW_HEIGHT / 15 && x > 14 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(14 * WINDOW_WIDTH / 19, 10 * WINDOW_HEIGHT / 15);
			}
			else if (starx > 9 * WINDOW_WIDTH / 15 && y < 5 * WINDOW_HEIGHT / 15 && x < 9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(9 * WINDOW_WIDTH / 19, 1 * WINDOW_HEIGHT / 15);
			}
			else if (stary > 5 * WINDOW_WIDTH / 15 && y < 5 * WINDOW_HEIGHT / 15 && x < 9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(1 * WINDOW_WIDTH / 19, 5 * WINDOW_HEIGHT / 15);
			}
			else if (starx > 9 * WINDOW_WIDTH / 15 && y > 9 * WINDOW_HEIGHT / 15 && x < 9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(9 * WINDOW_WIDTH / 19, 13 * WINDOW_HEIGHT / 15);
			}
			else if (stary < 9 * WINDOW_WIDTH / 15 && y >9 * WINDOW_HEIGHT / 15 && x < 9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(4 * WINDOW_WIDTH / 19, 9 * WINDOW_HEIGHT / 15);
			}
			else if (starx < 9 * WINDOW_WIDTH / 15 && y < 5 * WINDOW_HEIGHT / 15 && x>9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(9 * WINDOW_WIDTH / 19, 1 * WINDOW_HEIGHT / 15);
			}
			else if (stary > 5 * WINDOW_WIDTH / 15 && y < 5 * WINDOW_HEIGHT / 15 && x>9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(14 * WINDOW_WIDTH / 19, 5 * WINDOW_HEIGHT / 15);
			}
			else if (starx < 9 * WINDOW_WIDTH / 15 && y >9 * WINDOW_HEIGHT / 15 && x > 9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(9 * WINDOW_WIDTH / 19, 13 * WINDOW_HEIGHT / 15);
			}
			else if (stary < 9 * WINDOW_WIDTH / 15 && y>9 * WINDOW_HEIGHT / 15 && x > 9 * WINDOW_WIDTH / 19)
			{
				wParam = AIMoveTo(16 * WINDOW_WIDTH / 19, 9 * WINDOW_HEIGHT / 15);
			}
			else
			{
				wParam = AIMoveTo(starx, stary);
			}

		}
	}

	stop:Move(wParam, playertankx, playertanky);
}

WPARAM AITank::AIMoveTo(int posx, int posy)
{

	distance[0] = (x - posx)*(x - posx) + (y - WINDOW_HEIGHT / 15 - posy)*(y - WINDOW_HEIGHT / 15 - posy);
	distance[1] = (x - posx)*(x - posx) + (y + WINDOW_HEIGHT / 15 - posy)*(y + WINDOW_HEIGHT / 15 - posy);
	distance[2] = (x - WINDOW_WIDTH / 19 - posx)*(x - WINDOW_WIDTH / 19 - posx) + (y - posy)*(y - posy);
	distance[3] = (x + WINDOW_WIDTH / 19 - posx) * (x + WINDOW_WIDTH / 19 - posx) + (y - posy)*(y - posy);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4 - i - 1; j++)
		{
			if (distance[distancerank[j]] > distance[distancerank[j + 1]])
			{
				distancerank[j] = distancerank[j] + distancerank[j + 1];
				distancerank[j + 1] = distancerank[j] - distancerank[j + 1];
				distancerank[j] = distancerank[j] - distancerank[j + 1];
			}
		}
	}
	int dire;
	for (int i = 0; i <3; i++)
	{
		bool ifblocktheway=false;
		for (int j = 0; j < STONE_NUMBER; j++)
		{
			if (block[j].IfBlock(x, y, distancerank[i]))
			{
				ifblocktheway = true;
				break;
			}
		}
		if (ifblocktheway == false)
		{
			dire = distancerank[i];
			goto direstop;
		}

	}
direstop:switch (dire)
{
case 0:
	return VK_UP;
	break;
case 1:
	return VK_DOWN;
	break;
case 2:
	return VK_LEFT;
	break;
case 3:
	return VK_RIGHT;
	break;
default:
	break;
}

}

bool AITank::AIJudgeShot(int posx, int posy)
{
	if (posx >= x&&posy == y&& AIJudgeNoBlock(posx, posy, 3)&&direction==3)
	{
		return true;
	}	
	if (posx <= x&&posy == y&&AIJudgeNoBlock(posx, posy,2) && direction == 2)
	{
		return true;
	}	
	if (posx == x&&posy <= y&&AIJudgeNoBlock(posx, posy, 0) && direction == 0)
	{
		return true;
	}	
	if (posx == x&&posy >= y&&AIJudgeNoBlock(posx, posy, 1) && direction == 1)
	{
		return true;
	}
	return false;
}

bool AITank::AIJudgeNoBlock(int posx, int posy,int direc)
{
	bool noblock = true;
	int j = 0,i=0;
	switch (direc)
	{
	case 0:
		for (i = y - WINDOW_HEIGHT / 15; i >= posy+ WINDOW_HEIGHT / 15; i-= WINDOW_HEIGHT / 15)
		{
			for ( j = 0; j < STONE_NUMBER; j++)
			{
				if (block[j].x==posx&&block[j].y==i)
				{
					noblock = false;
					goto stop;
				}
			}
		}
		break;
	case 1:
		for ( i = y + WINDOW_HEIGHT / 15; i <= posy - WINDOW_HEIGHT / 15; i += WINDOW_HEIGHT / 15)
		{
			for ( j = 0; j < STONE_NUMBER; j++)
			{
				if (block[j].x == posx&&block[j].y == i)
				{
					noblock = false;
					goto stop;
				}
			}
		}
		break;
	case 2:
	{
		for (i = x- WINDOW_WIDTH / 19; i >= posx + WINDOW_WIDTH / 19; i -= WINDOW_WIDTH / 19)
		{
			for ( j = 0; j < STONE_NUMBER; j++)
			{
				if (block[j].x == i&&block[j].y == posy)
				{
					noblock = false;
					goto stop;
				}
			}
		}
	}
		break;
	case 3:
		for (i = x + WINDOW_WIDTH / 19; i <= posx - WINDOW_WIDTH / 19; i += WINDOW_WIDTH / 19)
		{
			for ( j = 0; j < STONE_NUMBER; j++)
			{
				if (block[j].x == i&&block[j].y == posy)
				{
					noblock = false;
					goto stop;
				}
			}
		}
		break;
	default:
		break;
	}
stop:	return noblock;
}
