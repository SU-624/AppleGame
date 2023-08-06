#include "AppleGame.h"
#include "define.h"

int g_EndGame = 0;

//paint���� �ҷ��ֱ�(ī��Ʈ �ٿ� ȭ�� �׸���)
void CheckTime(HWND hwnd, int* Remain_Time)
{
	if (g_Stage == g_Stage_Game)
	{
		if (1000 <= timeGetTime() - RecordedTime_forCheck)
		{
			//���� Remain_Time�� �ּҰ��� �Լ��� �Է°����� �޾ƿ��µ� �̶� �ʿ��� ���� Remain_Time�� 
			//�������� �ʿ���. �׸��� �̰� ���浵 �ؾ��ϴ� �޾ƿ� �ּҰ� ����ִ� ������ ���� �޾ƿ��� ����
			//*Remain_Time�� �����.
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
	hFont = CreateFont(30, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
	OldFont = (HFONT)SelectObject(MemDC, hFont);

	SetTextColor(MemDC, RGB(255, 255, 255));

	sprintf_s(OutputText, "%02d:%02d", Min, Second);
	SetBkMode(MemDC, TRANSPARENT);
	TextOut(MemDC, 700, 45, OutputText, strlen(OutputText));
	SelectObject(MemDC, OldFont);
	DeleteObject(hFont);
}