#include"ground.h"
#include"block.h"
#include"brush.h"
#include"tank.h"
#include"bullet.h"
#include"star.h"
#include"setting.h"
#include"broad.h"

#pragma  comment(lib,"Msimg32.lib")					//添加使用TransparentBlt函数所需的库文件

DWORD		g_tPre = 0, g_tNow = 0;					//声明l两个函数来记录时间,g_tPre记录上一次绘图的时间，g_tNow记录此次准备绘图的时间
int			g_iNum = 0;								//g_iNum用来记录图号，g_iX，g_iY分别表示贴图的横纵坐标
bool		messagebox = true;
int			gametime = GAME_TIME;
PlayerTank		playertank(2 * WINDOW_WIDTH / 19 , 12 * WINDOW_HEIGHT / 15, 0);
AITank			aitank(16 * WINDOW_WIDTH / 19,2 * WINDOW_HEIGHT / 15, 1);

LRESULT CALLBACK			WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);		//窗口过程函数
BOOL						Game_Init(HWND hwnd);												//在此函数中进行资源的初始化
VOID						Game_Paint(HWND hwnd);												//在此函数中进行绘图代码的书写
BOOL						Game_CleanUp(HWND hwnd);											//在此函数中进行资源的清理

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//设计窗口类
	WNDCLASSEX wndClass = { 0 };							//用WINDCLASSEX定义了一个窗口类
	wndClass.cbSize = sizeof(WNDCLASSEX);					//设置结构体的字节数大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW;				//设置窗口的样式
	wndClass.lpfnWndProc = WndProc;							//设置指向窗口过程函数的指针
	wndClass.cbClsExtra = 0;								//窗口类的附加内存，取0就可以了
	wndClass.cbWndExtra = 0;								//窗口的附加内存，依然取0就行了
	wndClass.hInstance = hInstance;							//指定包含窗口过程的程序的实例句柄。
	wndClass.hIcon = (HICON)::LoadImage(NULL, L"pic//tankgame.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //本地加载自定义ico图标
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);																		 //指定窗口类的光标句柄。
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);														 //为hbrBackground成员指定一个白色画刷句柄	
	wndClass.lpszMenuName = NULL;																						//用一个以空终止的字符串，指定菜单资源的名字。
	wndClass.lpszClassName = L"ForTheDreamOfGameDevelop";																//用一个以空终止的字符串，指定窗口类的名字。

	//注册窗口类	
	if (!RegisterClassEx(&wndClass))																	//设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
		return -1;

	//正式创建窗口	
	HWND hwnd = CreateWindow(L"ForTheDreamOfGameDevelop", WINDOW_TITLE,									//创建窗口函数CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	//窗口的移动、显示与更新
	MoveWindow(hwnd, 200, 0, WINDOW_WIDTH+16, WINDOW_HEIGHT+40+ 1.5 * WINDOW_HEIGHT / 19, true);		//调整窗口显示时的位置
	ShowWindow(hwnd, nShowCmd);																		    //调用ShowWindow函数来显示窗口
	UpdateWindow(hwnd);																					//对窗口进行更新

	//游戏资源的初始化，若初始化失败，弹出一个消息框，并返回FALSE
	if (!Game_Init(hwnd))
	{
		MessageBox(hwnd, L"资源初始化失败", L"消息窗口", 0);											//使用MessageBox函数，创建一个消息窗口
		return FALSE;
	}
	if (messagebox == true)
	{
		MessageBox(NULL, L"操作方式: 方向键移动, 空格键开火\n胜利条件: 击中敌方或在规定时间内收集到最多星星", L"提醒", 0);
		messagebox = false;
	}
	//消息循环过程
	MSG msg = { 0 };																					//定义并初始化msg
	while (msg.message != WM_QUIT)																		//使用while循环，如果消息不是WM_QUIT消息，就继续循环
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))														//查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			TranslateMessage(&msg);																		//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);																		//分发一个消息给窗口程序。
									
		}
		else
		{
			g_tNow = GetTickCount();   //获取当前系统时间
			if (g_tNow-g_tPre>=1000)
			{
				gametime--;
				g_tPre = GetTickCount();
			}
			if (gametime<0)
			{
				if (playertank.starnumber>aitank.starnumber)
				{
					MessageBox(NULL, L"你赢了, 按确定退出游戏", L"提醒", 0);
				}
				if (playertank.starnumber<aitank.starnumber)
				{
					MessageBox(NULL, L"你输了, 按确定退出游戏", L"提醒", 0);
				}
				if (playertank.starnumber==aitank.starnumber)
				{
					MessageBox(NULL, L"平局, 按确定退出游戏", L"提醒", 0);
				}
				DestroyWindow(hwnd);
			}
			Game_Paint(hwnd);
			if (playertank.exist==true&&aitank.exist==false)
			{
				MessageBox(NULL, L"你赢了, 按确定退出游戏", L"提醒", 0);
				DestroyWindow(hwnd);
			}
			if (playertank.exist == false && aitank.exist == true)
			{
				MessageBox(NULL, L"你输了, 按确定退出游戏", L"提醒", 0);
				DestroyWindow(hwnd);
			}
			if (playertank.exist == false && aitank.exist == false)
			{
				MessageBox(NULL, L"平局, 按确定退出游戏", L"提醒", 0);
				DestroyWindow(hwnd);
			}
		}

	}

	//窗口类的注销
	UnregisterClass(L"ForTheDreamOfGameDevelop", wndClass.hInstance);  //程序准备结束，注销窗口类
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)						//switch语句开始
	{

	case WM_KEYDOWN:	     //按下键盘消息
							 //判断按键的虚拟键码
		playertank.Move(wParam,aitank.x,aitank.y);
		break;
	case WM_DESTROY:					//若是窗口销毁消息
		Game_CleanUp(hwnd);			//调用自定义的资源清理函数Game_CleanUp（）进行退出前的资源清理
		PostQuitMessage(0);			//向系统表明有个线程有终止请求。用来响应WM_DESTROY消息
		break;									//跳出该switch语句

	default:										//若上述case条件都不符合，则执行该default语句
		return DefWindowProc(hwnd, message, wParam, lParam);		//调用缺省的窗口过程
	}

	return 0;									//正常退出
}

BOOL Game_Init(HWND hwnd)
{
	HBITMAP bmp;

	g_hdc = GetDC(hwnd);
	g_mdc = CreateCompatibleDC(g_hdc);  //创建一个和hdc兼容的内存DC
	g_bufdc = CreateCompatibleDC(g_hdc);//再创建一个和hdc兼容的缓冲DC
	bmp = CreateCompatibleBitmap(g_hdc, WINDOW_WIDTH, WINDOW_HEIGHT+ 1.5 * WINDOW_HEIGHT / 19);


	//g_iNum = 0;
	SelectObject(g_mdc, bmp);

	

	//设置石头树丛
	SetBlock();
	SetBrush();

	srand((unsigned)time(NULL));
	star.SetStar(playertank.x,playertank.y,aitank.x,aitank.y);

	Game_Paint(hwnd);
	return TRUE;
}

VOID Game_Paint(HWND hwnd)
{
	PaintGround();

	playertank.PaintTank(&aitank);

	aitank.AIAct(playertank.x,playertank.y,star.x,star.y);
	aitank.PaintTank(&playertank);

	PaintBrush();

	PaintBlock();

	star.PaintStar();

	PaintBroad(playertank.starnumber,aitank.starnumber,gametime);

	PaintTime(gametime, g_tNow, g_tPre);	

	//将最后的画面显示在窗口中
	BitBlt(g_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT+ 1.5 * WINDOW_HEIGHT / 19, g_mdc, 0, 0, SRCCOPY);
}

BOOL Game_CleanUp(HWND hwnd)
{
	//释放资源对象
	DeleteObject(g_hBackGround);
	DeleteObject(g_hBrush);
	DeleteObject(g_hBroad);
	DeleteObject(g_hBlock);
	DeleteDC(g_mdc);
	ReleaseDC(hwnd, g_hdc);
	return TRUE;
}