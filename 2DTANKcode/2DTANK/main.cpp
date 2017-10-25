#include"ground.h"
#include"block.h"
#include"brush.h"
#include"tank.h"
#include"bullet.h"
#include"star.h"
#include"setting.h"
#include"broad.h"

#pragma  comment(lib,"Msimg32.lib")					//���ʹ��TransparentBlt��������Ŀ��ļ�

DWORD		g_tPre = 0, g_tNow = 0;					//����l������������¼ʱ��,g_tPre��¼��һ�λ�ͼ��ʱ�䣬g_tNow��¼�˴�׼����ͼ��ʱ��
int			g_iNum = 0;								//g_iNum������¼ͼ�ţ�g_iX��g_iY�ֱ��ʾ��ͼ�ĺ�������
bool		messagebox = true;
int			gametime = GAME_TIME;
PlayerTank		playertank(2 * WINDOW_WIDTH / 19 , 12 * WINDOW_HEIGHT / 15, 0);
AITank			aitank(16 * WINDOW_WIDTH / 19,2 * WINDOW_HEIGHT / 15, 1);

LRESULT CALLBACK			WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);		//���ڹ��̺���
BOOL						Game_Init(HWND hwnd);												//�ڴ˺����н�����Դ�ĳ�ʼ��
VOID						Game_Paint(HWND hwnd);												//�ڴ˺����н��л�ͼ�������д
BOOL						Game_CleanUp(HWND hwnd);											//�ڴ˺����н�����Դ������

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//��ƴ�����
	WNDCLASSEX wndClass = { 0 };							//��WINDCLASSEX������һ��������
	wndClass.cbSize = sizeof(WNDCLASSEX);					//���ýṹ����ֽ�����С
	wndClass.style = CS_HREDRAW | CS_VREDRAW;				//���ô��ڵ���ʽ
	wndClass.lpfnWndProc = WndProc;							//����ָ�򴰿ڹ��̺�����ָ��
	wndClass.cbClsExtra = 0;								//������ĸ����ڴ棬ȡ0�Ϳ�����
	wndClass.cbWndExtra = 0;								//���ڵĸ����ڴ棬��Ȼȡ0������
	wndClass.hInstance = hInstance;							//ָ���������ڹ��̵ĳ����ʵ�������
	wndClass.hIcon = (HICON)::LoadImage(NULL, L"pic//tankgame.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //���ؼ����Զ���icoͼ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);																		 //ָ��������Ĺ������
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);														 //ΪhbrBackground��Աָ��һ����ɫ��ˢ���	
	wndClass.lpszMenuName = NULL;																						//��һ���Կ���ֹ���ַ�����ָ���˵���Դ�����֡�
	wndClass.lpszClassName = L"ForTheDreamOfGameDevelop";																//��һ���Կ���ֹ���ַ�����ָ������������֡�

	//ע�ᴰ����	
	if (!RegisterClassEx(&wndClass))																	//����괰�ں���Ҫ�Դ��������ע�ᣬ�������ܴ��������͵Ĵ���
		return -1;

	//��ʽ��������	
	HWND hwnd = CreateWindow(L"ForTheDreamOfGameDevelop", WINDOW_TITLE,									//�������ں���CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	//���ڵ��ƶ�����ʾ�����
	MoveWindow(hwnd, 200, 0, WINDOW_WIDTH+16, WINDOW_HEIGHT+40+ 1.5 * WINDOW_HEIGHT / 19, true);		//����������ʾʱ��λ��
	ShowWindow(hwnd, nShowCmd);																		    //����ShowWindow��������ʾ����
	UpdateWindow(hwnd);																					//�Դ��ڽ��и���

	//��Ϸ��Դ�ĳ�ʼ��������ʼ��ʧ�ܣ�����һ����Ϣ�򣬲�����FALSE
	if (!Game_Init(hwnd))
	{
		MessageBox(hwnd, L"��Դ��ʼ��ʧ��", L"��Ϣ����", 0);											//ʹ��MessageBox����������һ����Ϣ����
		return FALSE;
	}
	if (messagebox == true)
	{
		MessageBox(NULL, L"������ʽ: ������ƶ�, �ո������\nʤ������: ���ез����ڹ涨ʱ�����ռ����������", L"����", 0);
		messagebox = false;
	}
	//��Ϣѭ������
	MSG msg = { 0 };																					//���岢��ʼ��msg
	while (msg.message != WM_QUIT)																		//ʹ��whileѭ���������Ϣ����WM_QUIT��Ϣ���ͼ���ѭ��
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))														//�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ��
		{
			TranslateMessage(&msg);																		//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);																		//�ַ�һ����Ϣ�����ڳ���
									
		}
		else
		{
			g_tNow = GetTickCount();   //��ȡ��ǰϵͳʱ��
			if (g_tNow-g_tPre>=1000)
			{
				gametime--;
				g_tPre = GetTickCount();
			}
			if (gametime<0)
			{
				if (playertank.starnumber>aitank.starnumber)
				{
					MessageBox(NULL, L"��Ӯ��, ��ȷ���˳���Ϸ", L"����", 0);
				}
				if (playertank.starnumber<aitank.starnumber)
				{
					MessageBox(NULL, L"������, ��ȷ���˳���Ϸ", L"����", 0);
				}
				if (playertank.starnumber==aitank.starnumber)
				{
					MessageBox(NULL, L"ƽ��, ��ȷ���˳���Ϸ", L"����", 0);
				}
				DestroyWindow(hwnd);
			}
			Game_Paint(hwnd);
			if (playertank.exist==true&&aitank.exist==false)
			{
				MessageBox(NULL, L"��Ӯ��, ��ȷ���˳���Ϸ", L"����", 0);
				DestroyWindow(hwnd);
			}
			if (playertank.exist == false && aitank.exist == true)
			{
				MessageBox(NULL, L"������, ��ȷ���˳���Ϸ", L"����", 0);
				DestroyWindow(hwnd);
			}
			if (playertank.exist == false && aitank.exist == false)
			{
				MessageBox(NULL, L"ƽ��, ��ȷ���˳���Ϸ", L"����", 0);
				DestroyWindow(hwnd);
			}
		}

	}

	//�������ע��
	UnregisterClass(L"ForTheDreamOfGameDevelop", wndClass.hInstance);  //����׼��������ע��������
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)						//switch��俪ʼ
	{

	case WM_KEYDOWN:	     //���¼�����Ϣ
							 //�жϰ������������
		playertank.Move(wParam,aitank.x,aitank.y);
		break;
	case WM_DESTROY:					//���Ǵ���������Ϣ
		Game_CleanUp(hwnd);			//�����Զ������Դ������Game_CleanUp���������˳�ǰ����Դ����
		PostQuitMessage(0);			//��ϵͳ�����и��߳�����ֹ����������ӦWM_DESTROY��Ϣ
		break;									//������switch���

	default:										//������case�����������ϣ���ִ�и�default���
		return DefWindowProc(hwnd, message, wParam, lParam);		//����ȱʡ�Ĵ��ڹ���
	}

	return 0;									//�����˳�
}

BOOL Game_Init(HWND hwnd)
{
	HBITMAP bmp;

	g_hdc = GetDC(hwnd);
	g_mdc = CreateCompatibleDC(g_hdc);  //����һ����hdc���ݵ��ڴ�DC
	g_bufdc = CreateCompatibleDC(g_hdc);//�ٴ���һ����hdc���ݵĻ���DC
	bmp = CreateCompatibleBitmap(g_hdc, WINDOW_WIDTH, WINDOW_HEIGHT+ 1.5 * WINDOW_HEIGHT / 19);


	//g_iNum = 0;
	SelectObject(g_mdc, bmp);

	

	//����ʯͷ����
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

	//�����Ļ�����ʾ�ڴ�����
	BitBlt(g_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT+ 1.5 * WINDOW_HEIGHT / 19, g_mdc, 0, 0, SRCCOPY);
}

BOOL Game_CleanUp(HWND hwnd)
{
	//�ͷ���Դ����
	DeleteObject(g_hBackGround);
	DeleteObject(g_hBrush);
	DeleteObject(g_hBroad);
	DeleteObject(g_hBlock);
	DeleteDC(g_mdc);
	ReleaseDC(hwnd, g_hdc);
	return TRUE;
}