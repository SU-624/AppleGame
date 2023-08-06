#include "AppleGame.h"
#include "define.h"

int g_EndGame = 0;

//paint에서 불러주기(카운트 다운 화면 그리기)
void CheckTime(HWND hwnd, int* Remain_Time)
{
	if (g_Stage == g_Stage_Game)
	{
		if (1000 <= timeGetTime() - RecordedTime_forCheck)
		{
			//원본 Remain_Time의 주소값을 함수에 입력값으로 받아오는데 이때 필요한 것은 Remain_Time의 
			//변수값이 필요함. 그리고 이걸 변경도 해야하니 받아온 주소가 담겨있는 변수의 값을 받아오기 위해
			//*Remain_Time을 해줬다.
			*Remain_Time -= 1;
			RecordedTime_forCheck = timeGetTime();
			InvalidateRgn(hwnd, NULL, FALSE);
		}
		
		if (*Remain_Time <= 0)
		{
			g_Stage = g_Stage_Over;

			*Remain_Time = 0;
		}
	}


}

void Print_RemainTime(HDC MemDC, int Remain_Time)
{
	int Second = Remain_Time % 60;
	int Min = Remain_Time / 60;

	char OutputText[50];

	HFONT hFont, OldFont;
	hFont = CreateFont(30, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
	OldFont = (HFONT)SelectObject(MemDC, hFont);

	SetTextColor(MemDC, RGB(255, 255, 255));

	sprintf_s(OutputText, "%02d:%02d", Min, Second);
	SetBkMode(MemDC, TRANSPARENT);
	TextOut(MemDC, 700, 45, OutputText, strlen(OutputText));
	SelectObject(MemDC, OldFont);
	DeleteObject(hFont);
}