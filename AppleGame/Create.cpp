#include "AppleGame.h"
#include "define.h"
//#include "temp.h"


int g_GameBoard[Board_Y][Board_X];


//struct APPLE_CHECK {
//	POINT point1;
//	POINT point2;
//};
//
//struct APPLE_CHECK apple_check[Board_Y][Board_X];



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

			POINT point1, point2,point3,point4,point5;

			//apple에 5개 픽셀좌표 설정
			point1.x = basepoint.x + 1;
			point1.y = basepoint.y + 1;
			//
			point2.x = basepoint.x + 1;
			point2.y = basepoint.y + 1;
			//
			point3.x = basepoint.x + 1;
			point3.y = basepoint.y + 1;
			//
			point4.x = basepoint.x + 1;
			point4.y = basepoint.y + 1;
			//
			point5.x = basepoint.x + 1;
			point5.y = basepoint.y + 1;

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