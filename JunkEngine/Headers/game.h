#ifndef _GAME_H                 // �������� ����
#define _GAME_H                 
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <Mmsystem.h>
#include "graphics.h"
#include "input.h"
#include "constants.h"
#include "gameError.h"

class Game
{
protected:
    // ���� �Ӽ�
    Graphics *graphics;         // Graphics ��ü ������
    Input   *input;             // Input ��ü ������
    HWND    hwnd;               // ������ �ڵ�
    HRESULT hr;                 // ǥ�� ��ȯ Ÿ��
    LARGE_INTEGER timeStart;    // ���� ī���� ���۰�
    LARGE_INTEGER timeEnd;      // ���� ī���� ���� ��
    LARGE_INTEGER timerFreq;    // ���� ī���� �󵵼�
    float   frameTime;          // ������ �����ӿ� �ʿ��� �ð�
    float   fps;                // �ʴ� �����Ӽ�
    DWORD   sleepTime;          // ������ ������ ��� ���� �ð�
    bool    paused;             // ���� �Ͻ����� ����
    bool    initialized;        // �ʱ�ȭ

public:
    Game(); // ������
    virtual ~Game(); // �Ҹ���

    // --------- ��� �Լ� ---------//

	//������ �޼��� �ڵ鷯
    LRESULT messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

    // ���� �ʱ�ȭ
    virtual void initialize(HWND hwnd); // hwnd�� ������ �ڵ鷯
    virtual void run(HWND);				// �ݺ� ȣ��, ��� ����
    virtual void releaseAll();          // �׷��� ����̽� ����
    virtual void resetAll();			// ǥ�� ����� �� ��� ��ü ����
    virtual void deleteAll();           // ����� ��� �޸� ����
    virtual void renderGame();          // ���� ������

    virtual void handleLostGraphicsDevice(); // �ν�Ʈ ���°� �� �׷��� ����̽� ó��

    Graphics* getGraphics() {return graphics;}	// Graphics ��ü ������ ��ȯ
    Input* getInput()       {return input;}		// Input ��ü ������ ��ȯ

    void exitGame(){ // ���� ����
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	}
	// ------------------------------//

    virtual void update() = 0;		// ���ӿ�� ����
    virtual void ai() = 0;			// AI ���
    virtual void collisions() = 0;	// �浹 Ȯ��
    virtual void render() = 0;		// ������
};

#endif
