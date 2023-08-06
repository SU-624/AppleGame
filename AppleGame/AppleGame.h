#pragma once
#pragma comment(lib, "Msimg32.lib")

#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
//srand함수의 시드값을 시간으로 받기위한 헤더파일
#include <time.h>

// FMOD 사용을 위한 헤더파일
#include "Sound.h"

// 리소스 사용을 위한 헤더파일
#include "resource.h"

// 함수 선언 모음

// 윈도 프로시저의 선언부. 전방선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


// 게임 보드 배열을 만들고 초기화 합니다.
void CreateGameBoard();

// 마우스 좌표값 받아서 네모 그리는 함수
void DrawRect(HWND hWnd, BOOL bfill);

// Render함수들
void AppleBmpPrint(HDC hdc, HDC MemDC, int xPos, int yPos, int Select);

//사과를 지우고 사과 화면 좌표를 배열 인덱스에 대응시키는 함수
bool DeleteApple();

//타이머, 시간제한 함수
void CheckTime(HWND,int * Remain_Time);

//남은 시간을 출력해주는 함수
void Print_RemainTime(HDC, int);

//사과 점수 출력하는 함수
void PrintGameScore(HDC MemDC, int g_score);
//struct POS TransCoordinate();

//게임 중에 점수를 보여주는 함수
void PrintCheckScore(HDC MemDC, int g_Score);