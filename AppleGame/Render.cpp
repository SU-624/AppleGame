#include "AppleGame.h"
#include "define.h"

//HBITMAP g_hbmpMem;
HINSTANCE g_hInst;

// ��� ����ϱ�... (TransparentBlt) ���� �ִ� bmp ����ϱ�
void AppleBmpPrint(HDC MemDC, HDC BitDC, int xPos, int yPos, int Select)
{
	int tmp = g_GameBoard[yPos][xPos];

	if (tmp == 0)
	{
		HBITMAP MyBitmap =		// 1�� ������ٰ� +1�� �ؼ� ���� ��� �ҷ���
			LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_DELETEAPPLE));// + Select - 1));
		HBITMAP OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);
		BITMAP BitmapInfo;

		GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

		TransparentBlt(MemDC,
			65 + (xPos * 85), 92 + (yPos * 70),			// ����� ���� ��ġ
			BitmapInfo.bmWidth, BitmapInfo.bmHeight,
			BitDC, 0, 0,
			BitmapInfo.bmWidth, BitmapInfo.bmHeight,
			RGB(0, 255, 0)); // color key

		SelectObject(BitDC, OldBitmap);
		DeleteObject(MyBitmap);

	}
	else
	{
		HBITMAP MyBitmap =		// 1�� ������ٰ� +1�� �ؼ� ���� ��� �ҷ���
			LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_APPLE1));// + Select - 1));
		HBITMAP OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);
		BITMAP BitmapInfo;

		//////////////////////////////////////////////////////////////////////////
		char OutputText[50];
		HFONT hFont, OldFont;
		hFont = CreateFont(30, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
		OldFont = (HFONT)SelectObject(MemDC, hFont);
		SetTextColor(MemDC, RGB(255, 255, 255));

		GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

		/// ��������Ʈ
		TransparentBlt(MemDC,
			65 + (xPos * 85), 92 + (yPos * 70),			// ����� ���� ��ġ
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




