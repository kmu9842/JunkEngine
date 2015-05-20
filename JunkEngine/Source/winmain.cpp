#define _CRTDBG_MAP_ALLOC       // for detecting memory leaks
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>             // for detecting memory leaks
#include <crtdbg.h>             // for detecting memory leaks
#include "..\\Headers\\MainGame.h"

// �Լ� ������Ÿ��
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM); 

// ���� ������
MainGame *game = NULL;
HWND hwnd = NULL;

// ������ ���ø����̼� ��������(����)
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    // �޸� ������ �ִ��� �������Ҷ� üũ
    #if defined(DEBUG) | defined(_DEBUG)
        _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    MSG msg;

    // ���� ����
    game = new MainGame;

    // ������ ����
    if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
        return 1;

    try{
        game->initialize(hwnd);     

        // ���� �޼��� ����
        int done = 0;

		AllocConsole();
		freopen("CONOUT$", "wb", stdout);

        while (!done)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // ������ �޼��� Ȯ��
            {
                if (msg.message == WM_QUIT)
                    done = 1;

                TranslateMessage(&msg); // WinProc�� �޼��� ����
                DispatchMessage(&msg);
            } else game->run(hwnd);    // ���� ���� ����
        }
        SAFE_DELETE (game);     // ������ �޸𸮸� �����
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

    SAFE_DELETE (game);     // �������� �޸� ����
    return 0;
}

// ������ �̺�Ʈ �ݹ�
LRESULT WINAPI WinProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    return (game->messageHandler(hwnd, msg, wParam, lParam));
}

// ������ ����
bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow) 
{ 
    WNDCLASSEX wcx; 
 
	// Window Ŭ���� ����ü�� ���� �����쿡 ���� ������ ä��
    wcx.cbSize = sizeof(wcx);           // ����ü�� ũ�� 
    wcx.style = CS_HREDRAW | CS_VREDRAW;    // ũ�Ⱑ ���Ұ�� �ٽ� �׸�
    wcx.lpfnWndProc = WinProc;          // ������ ���ν����� ��ٸ�
    wcx.cbClsExtra = 0;                 // ������ Ŭ����,������ �޸𸮴� �ʿ� ����.
    wcx.cbWndExtra = 0;                 
    wcx.hInstance = hInstance;          // �ν��Ͻ��� �ڵ�
    wcx.hIcon = NULL; 
    wcx.hCursor = LoadCursor(NULL,IDC_ARROW);   // �̸� ���ǵ� ȭ��ǥ
    wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // ���
    wcx.lpszMenuName =  NULL;           // �޴� ���ҽ� �̸�
    wcx.lpszClassName = CLASS_NAME;     // ������ Ŭ������ �̸� 
    wcx.hIconSm = NULL;                 // ���� Ŭ���� ������
 
    // ������ Ŭ������ ���
    if (RegisterClassEx(&wcx) == 0)    // ��������
        return false;

    //������ Ǯ��ũ�� ����
    DWORD style;
    if (FULLSCREEN)
        style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
    else
        style = WS_OVERLAPPEDWINDOW;

    // ������ ����
    hwnd = CreateWindow(
        CLASS_NAME,             // ������ Ŭ���� �̸�
        GAME_TITLE,             // ����ǥ������ �ؽ�Ʈ
        style,                  // ������ ��Ÿ��
        CW_USEDEFAULT,          // �������� ������ġ
        CW_USEDEFAULT,          // ���� ��ġ
        GAME_WIDTH,             // ��
        GAME_HEIGHT,            // ����
        (HWND) NULL,            // �θ� ������ ����
        (HMENU) NULL,           // �޴� ����
        hInstance,              // ���ø����̼� �ν��Ͻ��� �ڵ�
        (LPVOID) NULL);         // ������ �Ű����� ����

    if (!hwnd) // ���� ����
        return false;

    if(!FULLSCREEN)             // �������� ���
    {
        // Ŭ���̾�Ʈ ������ âũ�� ����
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);   // ������ �� �κ� ũ��
        MoveWindow(hwnd,
                   0,                                           // ����
                   0,                                           // ��
                   GAME_WIDTH+(GAME_WIDTH-clientRect.right),    // ������
                   GAME_HEIGHT+(GAME_HEIGHT-clientRect.bottom), // �Ʒ���
                   TRUE);                                       // ������ �ٽ�ĥ��
    }

    // ������ ǥ��
    ShowWindow(hwnd, nCmdShow);

    return true;
}


