#include "AppleGame.h"
#include "define.h"
#include "Sound.h"

typedef struct _APPLE_CHECK {
	POINT point1; // 1
	POINT point2; // 2
	POINT point3;
	POINT point4;
	POINT point5;
}APPLE_CHECK;

APPLE_CHECK apple_check[Board_Y][Board_X];

struct POS g_pos;

int g_GameBoard[Board_Y][Board_X];

void CreateGameBoard()
{
	srand(time(NULL));
	//rand함수를 써서 1부터 9까지의 숫자를 배열에 넣는다.
	for (int y = 0; y < Board_Y; y++)
	{
		for (int x = 0; x < Board_X; x++)
		{
			int rand_Apple = (rand() % 11) + 1;
			POINT basepoint;
			basepoint.x = 65 + (x * 85);
			basepoint.y = 92 + (y * 70);

			POINT point1, point2, point3, point4, point5;

			//apple에 5개 픽셀좌표 설정
			point1.x = basepoint.x + 25;
			point1.y = basepoint.y + 35;
			//						 
			point2.x = basepoint.x + 40;
			point2.y = basepoint.y + 45;
			//						 
			point3.x = basepoint.x + 55;
			point3.y = basepoint.y + 35;
			//						 
			point4.x = basepoint.x + 30;
			point4.y = basepoint.y + 60;
			//						 
			point5.x = basepoint.x + 50;
			point5.y = basepoint.y + 60;

			APPLE_CHECK temp;

			temp.point1 = point1;
			temp.point2 = point2;
			temp.point3 = point3;
			temp.point4 = point4;
			temp.point5 = point5;

			apple_check[y][x] = temp;

			g_GameBoard[y][x] = rand_Apple;
		}
	}
}


struct POS TransCoordinate()
{
	POINT first;
	//first.x = (mx1 - 70) / 85;
	//first.y = (my1 - 90) / 72;

	POINT second;
	//second.x = (mx2 - 70) / 85;
	//second.y = (my2 - 90) / 72;

	if (mx1 < mx2)
	{
		first.x = (mx1 - 70) / 85;
		second.x = (mx2 - 70) / 85;
	}
	else
	{
		first.x = (mx2 - 70) / 85;
		second.x = (mx1 - 70) / 85;
	}

	if (my1 < my2)
	{
		first.y = (my1 - 90) / 72;
		second.y = (my2 - 90) / 72;
 	}
	else
	{
		first.y = (my2 - 90) / 72;
		second.y = (my1 - 90) / 72;
	}

	struct POS mypos;
	mypos.FirstPos = first;
	mypos.SecondPos = second;

	return mypos;
}



//struct POS ValidateCoord(struct POS pos,struct APPLE_CHECK apple)
//{
//	//struct POS pos = TransCoordinate();
//	for (int i = pos.FirstPos.y; i <= pos.SecondPos.y; i++)
//	{
//		for (int j = pos.FirstPos.x; j <= pos.SecondPos.x; j++)
//		{
//			//if (g_GameBoard[i][j])
//			//{
//
//			//}
//			//else if(in_rect(pos,))
//		}
//	}
//
//}

bool ValidateCoord(int num, APPLE_CHECK apple)
{
	int valid_num = 0;

	if (mx1 <= apple.point1.x && my1 <= apple.point1.y &&mx2>= apple.point1.x&& my2>=apple.point1.y)
	{
		valid_num += 1;
	}

	if (mx1 <= apple.point2.x && my1 <= apple.point2.y && mx2 >= apple.point2.x && my2 >= apple.point2.y)
	{
		valid_num += 1;
	}

	if (mx1 <= apple.point3.x && my1 <= apple.point3.y && mx2 >= apple.point3.x && my2 >= apple.point3.y)
	{
		valid_num += 1;
	}

	if (mx1 <= apple.point4.x && my1 <= apple.point4.y && mx2 >= apple.point4.x && my2 >= apple.point4.y)
	{
		valid_num += 1;
	}

	if (mx1 <= apple.point5.x && my1 <= apple.point5.y && mx2 >= apple.point5.x && my2 >= apple.point5.y)
	{
		valid_num += 1;
	}

	if (valid_num >= num)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//condition 값으로 준 숫자를 없애주는 기준으로 할 수 있음.
//default값은 10
bool Cal(int condition=10)
{
	struct POS pos = TransCoordinate();
	int result = 0;
	for (int i = pos.FirstPos.y; i <= pos.SecondPos.y; i++)
	{
		for (int j = pos.FirstPos.x; j <= pos.SecondPos.x; j++)
		{
			if (ValidateCoord(3,apple_check[i][j]))
			{
				if (g_GameBoard[i][j] <= 9)
				{
					result += g_GameBoard[i][j];
				}
				else
				{
					int minus = 0;

					// 마이너스 사과를 구현하기 위해서 숫자를 바꾼다.
					switch (g_GameBoard[i][j])
					{
					case 10:
						minus = -1;
						break;

					case 11:
						minus = -2;
						break;

					case 12:
						minus = -3;
						break;

					default:
						break;
					}

					result += minus;
				}
			}
			
		}
	}

	if (result == condition)
	{
		g_pos = pos;
		return true;
	}
	else
	{
		return false;
	}
}


bool DeleteApple()
{
	if (Cal())
	{
		//사과를 지운다
		for (int i = g_pos.FirstPos.y; i <= g_pos.SecondPos.y; i++)
		{
			for (int j = g_pos.FirstPos.x; j <= g_pos.SecondPos.x; j++)
			{
				if (ValidateCoord(3, apple_check[i][j]))
				{
					g_GameBoard[i][j] = 0;
					g_score += 1;
				}
			}
		}
		PlayEffect();
		return true;
	}
	else
	{
		// 그냥 놔둔다
		//if(BGM이 켜져있을 때)
		// 틀렸을때 소리
		//Sound_Stop(Channel_EFF1);
		//Sound_Play(EFF_2_NO, Channel_EFF1);
		return 0;
	}

}

void PrintGameScore(HDC MemDC, int g_score)
{
	char OutScoreText[50];
	
	HFONT hFont, OldFont;
	hFont = CreateFont(80, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
	OldFont = (HFONT)SelectObject(MemDC, hFont);
	SetTextColor(MemDC, RGB(255, 255, 255));

	sprintf_s(OutScoreText, "%d점", g_score);
	SetBkMode(MemDC, TRANSPARENT);
	TextOut(MemDC, 677, 445, OutScoreText, strlen(OutScoreText));
	SelectObject(MemDC, OldFont);
	DeleteObject(hFont);
}

void PrintCheckScore(HDC MemDC, int g_Score)
{
	char ScoreText[50];

	HFONT hFont, OldFont;
	hFont = CreateFont(30, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
	OldFont = (HFONT)SelectObject(MemDC, hFont);
	SetTextColor(MemDC, RGB(255, 255, 255));

	sprintf_s(ScoreText, "%d점", g_score);
	SetBkMode(MemDC, TRANSPARENT);
	TextOut(MemDC, 1300, 45, ScoreText, strlen(ScoreText));
	SelectObject(MemDC, OldFont);
	DeleteObject(hFont);
}
