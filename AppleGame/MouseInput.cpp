#include "AppleGame.h"
#include "define.h"

void DrawRect(HWND hWnd, BOOL bfill)
{
	int nStockBrush = NULL_BRUSH;
	HDC hdc = GetDC(hWnd);

	HBRUSH oldBrush = NULL, newBrush = NULL;

//HBRUSH newBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

	if (bfill)
	{
		newBrush = (HBRUSH)CreatePen(PS_SOLID, 1, NULL);
		oldBrush = (HBRUSH)(HPEN)SelectObject(hdc, newBrush);
		//SelectObject(hdc, newBrush);
		//SelectObject(hdc, GetStockObject(nStockBrush));
		SelectObject(hdc, oldBrush);
		DeleteObject(newBrush);
	}
	else
	{
		SetROP2(hdc, R2_NOT); // 기존꺼 지운다.
		
	}

	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, mx1, my1, mx2, my2);
	//SelectObject(hdc, oldBrush);
	//DeleteObject(newBrush);
	ReleaseDC(hWnd, hdc);

}

