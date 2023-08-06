#include "AppleGame.h"
#include "define.h"

//HBITMAP g_hbmpMem;
HINSTANCE g_hInst;

// 사과 출력하기... (TransparentBlt) 배경색 있는 bmp 출력하기
void AppleBmpPrint(HDC MemDC, HDC BitDC, int xPos, int yPos, int Select)
{
	int tmp = g_GameBoard[yPos][xPos];

	if (tmp == 0)
	{
		HBITMAP MyBitmap =		// 1번 사과에다가 +1씩 해서 다음 사과 불러옴
			LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_DELETEAPPLE));// + Select - 1));
		HBITMAP OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);
		BITMAP BitmapInfo;

		GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

		TransparentBlt(MemDC,
			65 + (xPos * 85), 92 + (yPos * 70),			// 사과를 놓을 위치
			BitmapInfo.bmWidth, BitmapInfo.bmHeight,
			BitDC, 0, 0,
			BitmapInfo.bmWidth, BitmapInfo.bmHeight,
			RGB(0, 255, 0)); // color key

		SelectObject(BitDC, OldBitmap);
		DeleteObject(MyBitmap);

	}
	else
	{
		HBITMAP MyBitmap =		// 1번 사과에다가 +1씩 해서 다음 사과 불러옴
			LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_APPLE1));// + Select - 1));
		HBITMAP OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);
		BITMAP BitmapInfo;

		//////////////////////////////////////////////////////////////////////////
		char OutputText[50];
		HFONT hFont, OldFont;
		hFont = CreateFont(30, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
		OldFont = (HFONT)SelectObject(MemDC, hFont);
		SetTextColor(MemDC, RGB(255, 255, 255));

		GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

		/// 스프라이트
		TransparentBlt(MemDC,
			65 + (xPos * 85), 92 + (yPos * 70),			// 사과를 놓을 위치
			BitmapInfo.bmWidth, BitmapInfo.bmHeight,
			BitDC, 0, 0,
			BitmapInfo.bmWidth, BitmapInfo.bmHeight,
			RGB(0, 255, 0)); // color key

		SelectObject(BitDC, OldBitmap);
		DeleteObject(MyBitmap);

		switch (tmp)
		{
		case 10:
			tmp = -1;
			sprintf_s(OutputText, "%d", tmp);
			SetBkMode(MemDC, TRANSPARENT);
			TextOut(MemDC, 65 + 30 + (xPos * 85), 92 + 30 + (yPos * 70),
				OutputText, strlen(OutputText));
			break;
		case 11:
			tmp = -2;
			sprintf_s(OutputText, "%d", tmp);
			SetBkMode(MemDC, TRANSPARENT);
			TextOut(MemDC, 65 + 30 + (xPos * 85), 92 + 30 + (yPos * 70),
				OutputText, strlen(OutputText));
			break;

		default:
			sprintf_s(OutputText, "%d", tmp);
			SetBkMode(MemDC, TRANSPARENT);
			TextOut(MemDC, 65 + 35 + (xPos * 85), 92 + 30 + (yPos * 70),
				OutputText, strlen(OutputText));
			break;
		}

		SelectObject(MemDC, OldFont);
		DeleteObject(hFont);
	}
}




