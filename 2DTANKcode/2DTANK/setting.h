#pragma once

#define WINDOW_WIDTH	760					//Ϊ���ڿ�ȶ���ĺ꣬�Է����ڴ˴��޸Ĵ��ڿ��
#define WINDOW_HEIGHT	600	 				//Ϊ���ڸ߶ȶ���ĺ꣬�Է����ڴ˴��޸Ĵ��ڸ߶�
#define WINDOW_TITLE	L"2D TANK GAME "	//Ϊ���ڱ��ⶨ��ĺ�
#define STONE_NUMBER	102					//ʯͷ��Ŀ	
#define BRUSH_NUMBER	35					//������ľ
#define BULLET_NUMBER	30					//��Ļ���ܳ���ͬһ��̹�˵��ӵ������Ŀ
#define HARDLEVEL		150					//ԽСAI�ٶ�Խ��
#define GAME_TIME		15
#define BULLET_SPEED	1					//ԽС�ӵ��ٶ�Խ��

#include <windows.h>
#include <tchar.h>							//ʹ��swprintf_s���������ͷ�ļ�

HDC		g_hdc = NULL, g_mdc = NULL, g_bufdc = NULL;      //ȫ���豸�������������ȫ���ڴ�DC���
