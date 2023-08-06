#pragma once

// 소리 채널 수 정의
#define SOUND_CHANNEL 5

//게임 보드의 숫자
#define Board_X 16
#define Board_Y 9

// 윈도우 사이즈 정의
#define WIN_Xpos 100
#define Win_Ypos 100
#define WIN_WIDTH 1520
#define WIN_HEIGHT 900

//게임 시간 타이머
#define COUNTDOWN_TIMER 1

// 사운드 목록
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

// 게임의 상태를 저장하는 변수
extern int g_Stage;

// 전역범위로 사용하는 변수 extern으로 모음
// Fomod 시스템을 컨트롤 하는 변수
static System* pSystem;

// 사과를 저장하는 배열 static을 쓰니 다른사과가 불려짐
extern int g_GameBoard[Board_Y][Board_X];

/// 비트맵 핸들 용도 : 메모리 비트맵
static HBITMAP g_hbmpMem;

///  비트맵 저장 
/// WinMain에서 초기화 필수!!!
/// static 사용하면 비트맥이 출력이 안됨
extern HINSTANCE g_hInst;

// 마우스 좌표
extern int mx1, my1, mx2, my2;

//게임 시간을 체크하기 위한 변수
extern int g_EndGame;


struct POS {
	POINT FirstPos;
	POINT SecondPos;
};

extern struct POS g_pos;

//현재 시간 기록용 변수(기록까지 시간이 얼마나 흘렀는지 체크)
static DWORD RecordedTime_forCheck;
//남은 시간 나타내는 변수
//extern int Remain_Time;

// 소리 조절 스크롤바
#define ID_SOUND_THIC 100

// 리셋 버튼 관련 변수
#define IDC_BUTTON1 101
static HWND  hwnd_Reset_Button;

//게임 스코어 계산하는 변수
extern  int g_score;
