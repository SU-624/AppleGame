#pragma once

// �Ҹ� ä�� �� ����
#define SOUND_CHANNEL 5

//���� ������ ����
#define Board_X 16
#define Board_Y 9

// ������ ������ ����
#define WIN_Xpos 100
#define Win_Ypos 100
#define WIN_WIDTH 1520
#define WIN_HEIGHT 900

//���� �ð� Ÿ�̸�
#define COUNTDOWN_TIMER 1

// ���� ���
typedef enum
{
	BGM_0_SOUND = 0,
	BGM_1_Miskate,
	BGM_2_Cat,
	BGM_3_,
	BGM_4_,

	EFF_1_OK = 5,
	EFF_2_NO,
	Eff_3_,
	EFF_4_,
	EFF_5_,

} Sound_List;

typedef enum
{
	Channel_BGM,
	Channel_EFF1,
	Channel_EFF2
} Sound_Channel;

typedef enum
{
	g_Stage_Title,
	g_Stage_Game,
	g_Stage_Over,
	g_Stage_Reset
} GAME_STAGE;

// ������ ���¸� �����ϴ� ����
extern int g_Stage;

// ���������� ����ϴ� ���� extern���� ����
// Fomod �ý����� ��Ʈ�� �ϴ� ����
static System* pSystem;

// ����� �����ϴ� �迭 static�� ���� �ٸ������ �ҷ���
extern int g_GameBoard[Board_Y][Board_X];

/// ��Ʈ�� �ڵ� �뵵 : �޸� ��Ʈ��
static HBITMAP g_hbmpMem;

///  ��Ʈ�� ���� 
/// WinMain���� �ʱ�ȭ �ʼ�!!!
/// static ����ϸ� ��Ʈ���� ����� �ȵ�
extern HINSTANCE g_hInst;

// ���콺 ��ǥ
extern int mx1, my1, mx2, my2;

//���� �ð��� üũ�ϱ� ���� ����
extern int g_EndGame;


struct POS {
	POINT FirstPos;
	POINT SecondPos;
};

extern struct POS g_pos;

//���� �ð� ��Ͽ� ����(��ϱ��� �ð��� �󸶳� �귶���� üũ)
static DWORD RecordedTime_forCheck;
//���� �ð� ��Ÿ���� ����
//extern int Remain_Time;

// �Ҹ� ���� ��ũ�ѹ�
#define ID_SOUND_THIC 100

// ���� ��ư ���� ����
#define IDC_BUTTON1 101
static HWND  hwnd_Reset_Button;

//���� ���ھ� ����ϴ� ����
extern  int g_score;
