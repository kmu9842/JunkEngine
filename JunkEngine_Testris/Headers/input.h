#ifndef _INPUT_H                
#define _INPUT_H                
#define WIN32_LEAN_AND_MEAN

class Input;

#include <windows.h>
#include <WindowsX.h>
#include <string>
#include <XInput.h>
#include "constants.h"
#include "gameError.h"

// ���� ���콺�� ���� ���� �߰� //
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif
//------------------------------//

namespace inputNS
{
    const int KEYS_ARRAY_LEN = 256;		// Ű �迭 ũ��
    
    const UCHAR KEYS_DOWN = 1;
    const UCHAR KEYS_PRESSED = 2;
    const UCHAR MOUSE = 4;
    const UCHAR TEXT_IN = 8;
    const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

const DWORD GAMEPAD_THUMBSTICK_DEADZONE = (DWORD)(0.20f * 0X7FFF);		// ������ 20%�� ���� ���� �⺻ ������ ����
const DWORD GAMEPAD_TRIGGER_DEADZONE = 30;								// Ʈ���� ���� 0~255
const DWORD MAX_CONTROLLERS = 4;										

// state.Gamepad.wButtons���� ���� �е� ��ư�� �ش��ϴ� ��Ʈ
const DWORD GAMEPAD_DPAD_UP        = 0x0001;
const DWORD GAMEPAD_DPAD_DOWN      = 0x0002;
const DWORD GAMEPAD_DPAD_LEFT      = 0x0004;
const DWORD GAMEPAD_DPAD_RIGHT     = 0x0008;
const DWORD GAMEPAD_START_BUTTON   = 0x0010;
const DWORD GAMEPAD_BACK_BUTTON    = 0x0020;
const DWORD GAMEPAD_LEFT_THUMB     = 0x0040;
const DWORD GAMEPAD_RIGHT_THUMB    = 0x0080;
const DWORD GAMEPAD_LEFT_SHOULDER  = 0x0100;
const DWORD GAMEPAD_RIGHT_SHOULDER = 0x0200;
const DWORD GAMEPAD_A              = 0x1000;
const DWORD GAMEPAD_B              = 0x2000;
const DWORD GAMEPAD_X              = 0x4000;
const DWORD GAMEPAD_Y              = 0x8000;

struct ControllerState
{
    XINPUT_STATE        state;
    XINPUT_VIBRATION    vibration;			// ����
    float               vibrateTimeLeft;    // �и���
    float               vibrateTimeRight;   
    bool                connected;
};

class Input
{
private:
    bool keysDown[inputNS::KEYS_ARRAY_LEN];     // Ư�� Ű�� ���� ��� true�� �Ǵ� �迭 
	bool keysUp[inputNS::KEYS_ARRAY_LEN];     // Ư�� Ű�� �� ��� true�� �Ǵ� �迭 
    bool keysPressed[inputNS::KEYS_ARRAY_LEN];  // ���� ������ �����ϴ� ���� Ư�� Ű�� ���� ��� true�� �Ǵ� �迭 
    std::string textIn;                         // ����ڰ� �Է��� �ؽ�Ʈ
    char charIn;                                // �������� �Է��� ����
    bool newLine;                               // ���ο� ���� ������ �� true�� �ȴ�.
    int  mouseX, mouseY;                        // ȭ�� ���� ���콺 ��ġ
    int  mouseRawX, mouseRawY;                  // ���� ���콺 ������
    RAWINPUTDEVICE Rid[1];                      // ���� ���콺��
    bool mouseCaptured;                         // ���콺�� ĸ�ĵ� ��� true�� ��
    bool mouseLButton;                          // ���콺 ���� ��ư�� ���� ��� true�� ��
    bool mouseMButton;                          // ���콺 ��� ��ư�� ���� ��� true�� ��
    bool mouseRButton;                          // ���콺 ������ ��ư�� ���� ��� true�� ��
    bool mouseX1Button;                         // ���콺 X1 ��ư�� ���� ��� true�� ��
    bool mouseX2Button;                         // ���콺 X2�� ��ư�� ���� ��� true�� ��
    ControllerState controllers[MAX_CONTROLLERS];    // ��Ʈ�ѷ� ����

public:
    Input(); // ������
    virtual ~Input(); // �Ҹ���

    void initialize(HWND hwnd, bool capture); // �Է� �ʱ�ȭ

    void keyDown(WPARAM);	// Ű ���� ����
    void keyUp(WPARAM);
    void keyIn(WPARAM);		// textIn�� �Է��� ���ڸ� ����

	bool isKeyUp(UCHAR vkey);			//	
    bool isKeyDown(UCHAR vkey) const;		// ����Ű�� ������ ��� true����
    bool wasKeyPressed(UCHAR vkey) const;	// ���� �ֱ� �����ӿ� Ư�� ����Ű�� ������ ��� true��ȯ
    bool anyKeyPressed() const;				// ���� �ֱٿ� �ƹ� Ű�� ������ ��� true ��ȯ 

    void clearKeyPress(UCHAR vkey);						// Ư�� Ű �Է� ���� Ŭ����
    void clear(UCHAR what);								// Ư�� �Է¹��� Ŭ����
    void clearAll() {clear(inputNS::KEYS_MOUSE_TEXT);}	// ��� �Է� ���� Ŭ����
    void clearTextIn() {textIn.clear();}				// �Էµ� �ؽ�Ʈ Ŭ����

    std::string getTextIn() {return textIn;} // �Է��� �ؽ�Ʈ�� string���� ��ȯ
    char getCharIn()        {return charIn;} // �������� �Է��� ���ڸ� ��ȯ

    void mouseIn(LPARAM);		// ���콺 ��ǥ���� mouseX, mouseY�� ����
    void mouseRawIn(LPARAM);	// ���� ���콺 ��ǥ���� mouseRawX, mouseRawY�� ����

	//---- ���콺 ��ư ���� ���� ----//
    void setMouseLButton(bool b) { mouseLButton = b; } 
    void setMouseMButton(bool b) { mouseMButton = b; } 
    void setMouseRButton(bool b) { mouseRButton = b; } 
    void setMouseXButton(WPARAM wParam) {mouseX1Button = (wParam & MK_XBUTTON1) ? true:false;
                                         mouseX2Button = (wParam & MK_XBUTTON2) ? true:false;}
    //-------------------------------//

	// ���콺 ��ġ�� ��ȯ
    int  getMouseX()        const { return mouseX; }
    int  getMouseY()        const { return mouseY; }

	// ���� ���콺 ��ġ�� ��ȯ
    int  getMouseRawX()     const { return mouseRawX; }
    int  getMouseRawY()     const { return mouseRawY; }

    // ��ư ���� ��ȯ
    bool getMouseLButton()  const { return mouseLButton; }
    bool getMouseMButton()  const { return mouseMButton; }
    bool getMouseRButton()  const { return mouseRButton; }
    bool getMouseX1Button() const { return mouseX1Button; }
    bool getMouseX2Button() const { return mouseX2Button; }

	
    void checkControllers();	// ��Ʈ�ѷ� üũ
    void readControllers();		// ��Ʈ�ѷ� �о��

	// ������ ��Ʈ�ѷ��� ���¸� ��ȯ�Ѵ�.
    const ControllerState* getControllerState(UINT n)
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return &controllers[n];
    }

    // ��Ʈ�ѷ� n�� ��ư ���¸� ��ȯ�Ѵ�.
    const WORD getGamepadButtons(UINT n)
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return controllers[n].state.Gamepad.wButtons;
    }

	//----- ��Ʈ�ѷ� ��ư ���� ��ȯ -----//
    bool getGamepadDPadUp(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_UP) != 0);
    } //
    bool getGamepadDPadDown(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_DOWN) != 0);
    }
    bool getGamepadDPadLeft(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return ((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_LEFT) != 0);
    }
	bool getGamepadDPadRight(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_DPAD_RIGHT) != 0);
    }
    bool getGamepadStart(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_START_BUTTON) != 0);
    }
    bool getGamepadBack(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_BACK_BUTTON) != 0);
    }
    bool getGamepadLeftThumb(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_THUMB) != 0);
    }
    bool getGamepadRightThumb(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_THUMB) != 0);
    }
    bool getGamepadLeftShoulder(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_LEFT_SHOULDER) != 0);
    }
    bool getGamepadRightShoulder(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_RIGHT_SHOULDER) != 0);
    }
    bool getGamepadA(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_A) != 0);
    }
    bool getGamepadB(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_B) != 0);
    }
    bool getGamepadX(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_X) != 0);
    }
    bool getGamepadY(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return bool((controllers[n].state.Gamepad.wButtons&GAMEPAD_Y) != 0);
    }
	//-----------------------------------//

    // ��Ʈ�ѷ��� �Ƴ��α� ��Ʈ�ѷ� ���� ��ȯ //
    BYTE getGamepadLeftTrigger(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return (controllers[n].state.Gamepad.bLeftTrigger);
    }
    BYTE getGamepadRightTrigger(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return (controllers[n].state.Gamepad.bRightTrigger);
    }
    SHORT getGamepadThumbLX(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return (controllers[n].state.Gamepad.sThumbLX);
    }
    SHORT getGamepadThumbLY(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return (controllers[n].state.Gamepad.sThumbLY);
    }
    SHORT getGamepadThumbRX(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return (controllers[n].state.Gamepad.sThumbRX);
    }
    SHORT getGamepadThumbRY(UINT n) 
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return (controllers[n].state.Gamepad.sThumbRY);
    }
	//----------------------------------------//

	// ��Ʈ�ѷ� ���� ȿ��, �ӵ� 0 = ������, 65535 = 100%, sec�� ������ �� ���� �ð�
    void gamePadVibrateLeft(UINT n, WORD speed, float sec)
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        controllers[n].vibration.wLeftMotorSpeed = speed;
        controllers[n].vibrateTimeLeft = sec;
    }
    void gamePadVibrateRight(UINT n, WORD speed, float sec)
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        controllers[n].vibration.wRightMotorSpeed = speed;
        controllers[n].vibrateTimeRight = sec;
    }

    void vibrateControllers(float frameTime); // ��Ʈ�ѷ� ���� ȿ��
};

#endif

