/// AppleGame.cpp
/// 사과게임을 만들어보자
/// 헤더파일은 아래 두개만 넣으면 된다.
///

// 헤더파일과 함수 모음
#include "AppleGame.h"
// 전역변수들 모음
#include "define.h"

bool mouse = false;
int Remain_Time;
int mx1, my1, mx2, my2;
int g_Stage;
int g_score;
int dropApple = 0;

// 현재 그림을 그리고 있는지 여부
BOOL g_IsDrawing = FALSE;

// DrawRect 함수 활성화 여부
BOOL g_DrawRect = FALSE;

HWND sScroll;
int sound_Scroll = 5;

bool lastTime = true;


/// WinMain 함수 : 윈도즈 프로그램의 최초 진입점 ( Entry Point )
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR	lpCmdLine, int nCmdShow)
{
	char szAppName[] = "APPLE GAME";
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;

	//렌더링 테스트용 비트맵 출력에 필요한 변수
	g_hInst = hInstance;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	/// 윈도 클래스 등록
	RegisterClass(&wndclass);

	/// 윈도 생성
	hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
		WIN_Xpos, Win_Ypos, WIN_WIDTH, WIN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	/// 생성된 윈도를 화면에 표시
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	/// 메시지 루프
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			//if (g_Stage == g_Stage_Game || g_Stage == g_Stage_Over || g_Stage == g_Stage_Reset)
			//{
			//}
			if (dropApple >= 1)
			{
				InvalidateRgn(hWnd, NULL, FALSE);
			}
			CheckTime(hWnd, &Remain_Time);
			Sleep(10);
			// FMOD 사용을 위한 업데이트 함수
			pSystem->update();
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//HDC			hdc;
	HDC hdc;// = GetDC(hWnd);
	HDC			MemDC;
	HDC			BitDC;

	PAINTSTRUCT ps;
	HBITMAP		MyBitmap, OldBitmap;
	BITMAP		BitmapInfo;

	switch (message)
	{
		case WM_CREATE:
		{
			g_score = 0;
			//남은시간 120초로 초기화
			//게임시작 할 때 게임 리셋, 게임 종료 시 초기화를 해줘야함.
			Remain_Time = 120;
			CreateGameBoard();

			// 사운드 출력 준비
			SoundSystem(SOUND_CHANNEL);

			// BGM 출력
			Sound_All_OFF();
			Sound_BGM_ON(BGM_1_Miskate);

			// 소리조절 수평 스크롤바 생성
			sScroll = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
				1100, 765, 200, 20, hWnd, (HMENU)ID_SOUND_THIC, g_hInst, NULL);

			SetScrollRange(sScroll, SB_CTL, 0, 10, TRUE);
			SetScrollPos(sScroll, SB_CTL, sound_Scroll, TRUE);

			// 타이틀로 돌아가는 버튼 생성
			hwnd_Reset_Button =
				CreateWindow("button",		// 정의된 클래스 이름
					"타이틀로",				// 버튼의 이름
					WS_CHILD | WS_VISIBLE | // 자식 윈도우, 최초표시여부
					BS_PUSHBUTTON,          // 콘트롤 스타일
					800, 750, 150, 50,		// 좌표와 크기
					hWnd,
					(HMENU)IDC_BUTTON1,     // 콘트롤 ID
					g_hInst,
					NULL);


		}
		break;

		case WM_HSCROLL:
		{
			// 임시 핸들
			int Temp = sound_Scroll;

			switch (LOWORD(wParam))
			{
				/// 소리조절 스크롤바 컨트롤 코드
				/// 범위값 초과 여부 점검
				// 버튼을 누를 때
				case SB_LINELEFT:
					Temp = max(0, Temp - 1);
					break;
				case SB_LINERIGHT:
					Temp = min(10, Temp + 1);
					break;
					// 빈 공간을 누를 때
				case SB_PAGELEFT:
					Temp = max(0, Temp - 3);
					break;
				case SB_PAGERIGHT:
					Temp = min(10, Temp + 3);
					break;
				case SB_THUMBTRACK:
					Temp = HIWORD(wParam);
					break;

			}

			sound_Scroll = Temp;
			float sound = (float)sound_Scroll / 10;
			Sound_VOL_Set(Channel_BGM, sound);
			SetScrollPos((HWND)lParam, SB_CTL, sound_Scroll, TRUE);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;


		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				/// 버튼 컨트롤 코드
				case IDC_BUTTON1:

					g_Stage = g_Stage_Reset;
					EnableWindow(hwnd_Reset_Button, FALSE);
					SetFocus(hWnd);
					InvalidateRect(hWnd, NULL, FALSE);

					break;

			}
		}
		break;




		case WM_LBUTTONDOWN:
		{
			if (!mouse && g_Stage != g_Stage_Over)
			{
				// 버튼이 처음 눌렸으면... 저장하고 눌렸음을 표시한다.
				// lParam 안에 있는 x와 y좌표정보를 가져와서 저장한다.
				mx1 = mx2 = LOWORD(lParam);
				my1 = my2 = HIWORD(lParam);

				mouse = true;
			}

			if (g_DrawRect == TRUE)
			{
				// 그림이 그려지는 시작점 세팅
				mx1 = mx2 = LOWORD(lParam);
				my1 = my2 = HIWORD(lParam);

				SetCapture(hWnd);
				g_IsDrawing = TRUE;
				SetCursor(LoadCursor(NULL, IDC_CROSS));
				InvalidateRect(hWnd, NULL, FALSE);
			}
			break;
		}
		break;

		case WM_MOUSEMOVE:
		{
			if (g_IsDrawing)
			{
				SetCursor(LoadCursor(NULL, IDC_CROSS));
				DrawRect(hWnd, FALSE); // 기존꺼를 지워준다
				mx2 = LOWORD(lParam);
				my2 = HIWORD(lParam);
				DrawRect(hWnd, FALSE);

			}
			break;
		}
		break;

		case WM_LBUTTONUP:
		{
			if (mouse)
			{
				mx2 = LOWORD(lParam);
				my2 = HIWORD(lParam);
				if (mx1 > mx2)
				{
					int temp = mx2;
					mx2 = mx1;
					mx1 = temp;
				}

				if (my1 > my2)
				{
					int temp = my2;
					my2 = my1;
					my1 = temp;
				}
				mouse = false;

				// 사과를 지웠을 때만 화면을 갱신한다.
				if (DeleteApple())
				{
					dropApple = 1;

					//Sound_Play(EFF_1_OK, Channel_BGM);

					InvalidateRect(hWnd, NULL, FALSE);
				}

			}


			if (g_IsDrawing)
			{
				DrawRect(hWnd, FALSE);
				g_IsDrawing = FALSE;
				ReleaseCapture();

				InvalidateRect(hWnd, NULL, FALSE);
				UpdateWindow(hWnd);
				DrawRect(hWnd, TRUE);
			}
			break;

		}

		case WM_PAINT:
		{
			bool currentbuff = FALSE;
			hdc = BeginPaint(hWnd, &ps);
			MemDC = CreateCompatibleDC(hdc);
			BitDC = CreateCompatibleDC(hdc);

			HBITMAP hMemBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
			SelectObject(MemDC, hMemBitmap);

			// 비트맵을 생성하고 연결한 뒤, 흰색으로 덮는다.
			PatBlt(MemDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS);


			// 가상 화면이 실제로는 비트맵이라고 했잖아.
			// 근데 MemDC를 만들고, 그 비트맵을 가리킨 적이 없어.

			// 1개가 실제 화면 DC의 핸들 -> hdc
			// 1개가 메모리 비트맵 (=백버퍼 화면)의 핸들 -> MemDC
			// 나머지 아직 없어보이는 한개가 로드한 비트맵을 가리키는 핸들 -> ??? BitDC



			// 게임 상태 변화. 스페이스를 누르면 번화함.
			if (g_Stage == g_Stage_Title)
			{
				MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND1));
				OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);

				GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

				BitBlt(MemDC,
					2, 25,
					BitmapInfo.bmWidth, BitmapInfo.bmHeight,
					BitDC,
					0, 0, SRCCOPY);


				// 타이틀 1
				MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TITLE1));
				OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);

				GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

				BitBlt(MemDC,
					60, 40,
					BitmapInfo.bmWidth * 1.2, BitmapInfo.bmHeight,
					BitDC,
					0, 0, SRCCOPY);

				// 타이틀 2
				MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_TITLE2));
				OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);

				GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

				BitBlt(MemDC,
					740, 60,
					BitmapInfo.bmWidth * 1.2, BitmapInfo.bmHeight,
					BitDC,
					0, 0, SRCCOPY);

				DeleteObject(MyBitmap);

				if (g_DrawRect == TRUE)
				{
					DrawRect(hWnd, TRUE);
				}
				else
				{

				}


			}

			else if (g_Stage == g_Stage_Game)
			{

				MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND1));
				OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);
				//게임시작시 현재시간 기록
				RecordedTime_forCheck = timeGetTime();

				GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

				BitBlt(MemDC,
					2, 25,
					BitmapInfo.bmWidth, BitmapInfo.bmHeight,
					BitDC,
					0, 0, SRCCOPY);

				SelectObject(BitDC, OldBitmap);
				DeleteObject(MyBitmap);

				MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND2));
				OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);

				GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

				BitBlt(MemDC,
					70, 90,
					BitmapInfo.bmWidth, BitmapInfo.bmHeight,
					BitDC,
					50, 50, SRCCOPY);

				DeleteObject(MyBitmap);

				for (int y = 0; y < Board_Y; y++)
				{
					for (int x = 0; x < Board_X; x++)
					{
						AppleBmpPrint(MemDC, BitDC, x, y, g_GameBoard[y][x]);
					}
				}
				Print_RemainTime(MemDC, Remain_Time);

				//PrintGameScore(MemDC, g_score);

				g_DrawRect = TRUE;

				PrintCheckScore(MemDC, g_score);

				// DropApple
				if (dropApple >= 1)
				{
					MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_APPLE_EFFECT));
					OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);

					GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

					if (dropApple < 12)
					{
						TransparentBlt(MemDC,
							mx2 + dropApple * 5, my2 + dropApple * 20,			// 사과를 놓을 위치
							BitmapInfo.bmWidth, BitmapInfo.bmHeight,
							BitDC, 0, 0,
							BitmapInfo.bmWidth, BitmapInfo.bmHeight,
							RGB(0, 255, 0)); // color key
					}

					dropApple++;
					if (dropApple >= 14)
					{
						dropApple = 0;
					}
				}


				DeleteObject(MyBitmap);


				EnableWindow(hwnd_Reset_Button, TRUE);
			}

			else if (g_Stage == g_Stage_Over)
			{
				MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND1));
				OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);

				GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

				BitBlt(MemDC,
					2, 25,
					BitmapInfo.bmWidth, BitmapInfo.bmHeight,
					BitDC,
					0, 0, SRCCOPY);

				DeleteObject(MyBitmap);

				MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND2));
				OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);

				GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

				BitBlt(MemDC,
					70, 90,
					BitmapInfo.bmWidth, BitmapInfo.bmHeight,
					BitDC,
					50, 50, SRCCOPY);

				DeleteObject(MyBitmap);

				for (int y = 0; y < Board_Y; y++)
				{
					for (int x = 0; x < Board_X; x++)
					{
						AppleBmpPrint(MemDC, BitDC, x, y, g_GameBoard[y][x]);
					}
				}
				Print_RemainTime(MemDC, Remain_Time);

				MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_APPLESCORE));
				OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);

				GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

				TransparentBlt(MemDC, 580, 250,			// 사과를 놓을 위치
					BitmapInfo.bmWidth, BitmapInfo.bmHeight,
					BitDC, 0, 0,
					BitmapInfo.bmWidth, BitmapInfo.bmHeight,
					RGB(0, 255, 0));

				SelectObject(BitDC, OldBitmap);
				DeleteObject(MyBitmap);

				PrintGameScore(MemDC, g_score);
			}

			else if (g_Stage == g_Stage_Reset)
			{
				g_Stage = g_Stage_Title;
				Remain_Time = 120;
				CreateGameBoard();
				lastTime = true;
				g_score = 0;

				InvalidateRect(hWnd, NULL, FALSE);
			}


			// 항상 출력해야하는것.
			// 스피커 그림

			MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_SOUND_ON));
			OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);

			GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

			TransparentBlt(MemDC,
				1325, 725,
				BitmapInfo.bmWidth, BitmapInfo.bmHeight,
				BitDC, 0, 0,
				BitmapInfo.bmWidth, BitmapInfo.bmHeight,
				RGB(14, 209, 69)); // color key




			DeleteObject(MyBitmap);

			MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_SOUND_OFF));
			OldBitmap = (HBITMAP)SelectObject(BitDC, MyBitmap);

			GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);

			TransparentBlt(MemDC,
				1000, 725,
				BitmapInfo.bmWidth, BitmapInfo.bmHeight,
				BitDC, 0, 0,
				BitmapInfo.bmWidth, BitmapInfo.bmHeight,
				RGB(14, 209, 69)); // color key

			DeleteObject(MyBitmap);



			// 메모리 버퍼를 화면에 출력한다.
			BitBlt(hdc,
				0, 0,
				WIN_WIDTH, WIN_HEIGHT,
				MemDC, 0, 0, SRCCOPY);

			DeleteDC(BitDC);
			EndPaint(hWnd, &ps);
		}
		break;


		case WM_KEYDOWN:
		{
			if (GetAsyncKeyState(VK_SPACE) && g_Stage == g_Stage_Title)
			{
				g_Stage = g_Stage_Game;
				InvalidateRect(hWnd, NULL, FALSE);		// 윈도를 새로 그린다.
			}

			if (GetAsyncKeyState(VK_DELETE) && g_Stage == g_Stage_Game && lastTime)
			{
				Remain_Time += 10;
				lastTime = false;
				InvalidateRect(hWnd, NULL, FALSE);
			}
		}
		break;

		case WM_DESTROY:
		{
			// 생성되어있는 버퍼 비트맵 제거
			if (g_hbmpMem)	DeleteObject(g_hbmpMem);
			PostQuitMessage(0);
		}
		break;

		default:
		{
			return DefWindowProc(hWnd,
				message, wParam, lParam);
		}
	}
	return 0;
}
