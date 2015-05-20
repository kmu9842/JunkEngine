#define _CRTDBG_MAP_ALLOC       // for detecting memory leaks
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>             // for detecting memory leaks
#include <crtdbg.h>             // for detecting memory leaks
#include "..\\Headers\\MainGame.h"

// 함수 프로토타입
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM); 

// 게임 포인터
MainGame *game = NULL;
HWND hwnd = NULL;

// 윈도우 어플리케이션 시작지점(메인)
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    // 메모리 누수가 있는지 컴파일할때 체크
    #if defined(DEBUG) | defined(_DEBUG)
        _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    MSG msg;

    // 게임 생성
    game = new MainGame;

    // 윈도우 생성
    if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
        return 1;

    try{
        game->initialize(hwnd);     

        // 메인 메세지 루프
        int done = 0;

		AllocConsole();
		freopen("CONOUT$", "wb", stdout);

        while (!done)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // 윈도우 메세지 확인
            {
                if (msg.message == WM_QUIT)
                    done = 1;

                TranslateMessage(&msg); // WinProc에 메세지 전달
                DispatchMessage(&msg);
            } else game->run(hwnd);    // 게임 루프 실행
        }
        SAFE_DELETE (game);     // 종료전 메모리를 비워줌
        return msg.wParam;
    }
    catch(const GameError &err)
    {
        game->deleteAll();
        DestroyWindow(hwnd);
        MessageBox(NULL, err.getMessage(), "Error", MB_OK);
    }
    catch(...)
    {
        game->deleteAll();
        DestroyWindow(hwnd);
        MessageBox(NULL, "Unknown error occured in game.", "Error", MB_OK);
    }

    SAFE_DELETE (game);     // 나가기전 메모리 해제
    return 0;
}

// 윈도우 이벤트 콜백
LRESULT WINAPI WinProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    return (game->messageHandler(hwnd, msg, wParam, lParam));
}

// 윈도우 생성
bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow) 
{ 
    WNDCLASSEX wcx; 
 
	// Window 클래스 구조체를 메인 윈도우에 대한 변수로 채움
    wcx.cbSize = sizeof(wcx);           // 구조체의 크기 
    wcx.style = CS_HREDRAW | CS_VREDRAW;    // 크기가 변할경우 다시 그림
    wcx.lpfnWndProc = WinProc;          // 윈도우 프로시저를 기다림
    wcx.cbClsExtra = 0;                 // 여분의 클래스,윈도우 메모리는 필요 없음.
    wcx.cbWndExtra = 0;                 
    wcx.hInstance = hInstance;          // 인스턴스의 핸들
    wcx.hIcon = NULL; 
    wcx.hCursor = LoadCursor(NULL,IDC_ARROW);   // 미리 정의된 화살표
    wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // 배경
    wcx.lpszMenuName =  NULL;           // 메뉴 리소스 이름
    wcx.lpszClassName = CLASS_NAME;     // 윈도우 클래스의 이름 
    wcx.hIconSm = NULL;                 // 작은 클래스 아이콘
 
    // 윈도우 클래스를 등록
    if (RegisterClassEx(&wcx) == 0)    // 에러감지
        return false;

    //윈도우 풀스크린 여부
    DWORD style;
    if (FULLSCREEN)
        style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
    else
        style = WS_OVERLAPPEDWINDOW;

    // 윈도우 생성
    hwnd = CreateWindow(
        CLASS_NAME,             // 윈도우 클래스 이름
        GAME_TITLE,             // 제목표시줄의 텍스트
        style,                  // 윈도우 스타일
        CW_USEDEFAULT,          // 윈도우의 수평위치
        CW_USEDEFAULT,          // 수직 위치
        GAME_WIDTH,             // 폭
        GAME_HEIGHT,            // 넓이
        (HWND) NULL,            // 부모 윈도우 없음
        (HMENU) NULL,           // 메뉴 없음
        hInstance,              // 어플리케이션 인스턴스의 핸들
        (LPVOID) NULL);         // 윈도우 매개변수 없음

    if (!hwnd) // 에러 감지
        return false;

    if(!FULLSCREEN)             // 윈도우일 경우
    {
        // 클라이언트 영역의 창크기 조정
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);   // 윈도우 각 부분 크기
        MoveWindow(hwnd,
                   0,                                           // 왼쪽
                   0,                                           // 위
                   GAME_WIDTH+(GAME_WIDTH-clientRect.right),    // 오른쪽
                   GAME_HEIGHT+(GAME_HEIGHT-clientRect.bottom), // 아래쪽
                   TRUE);                                       // 윈도우 다시칠함
    }

    // 윈도우 표시
    ShowWindow(hwnd, nCmdShow);

    return true;
}


