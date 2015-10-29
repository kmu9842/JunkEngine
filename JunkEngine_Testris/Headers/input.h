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

// 정밀 마우스를 쓰기 위해 추가 //
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif
//------------------------------//

namespace inputNS
{
    const int KEYS_ARRAY_LEN = 256;		// 키 배열 크기
    
    const UCHAR KEYS_DOWN = 1;
    const UCHAR KEYS_PRESSED = 2;
    const UCHAR MOUSE = 4;
    const UCHAR TEXT_IN = 8;
    const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

const DWORD GAMEPAD_THUMBSTICK_DEADZONE = (DWORD)(0.20f * 0X7FFF);		// 범위의 20%를 데드 존의 기본 값으로 설정
const DWORD GAMEPAD_TRIGGER_DEADZONE = 30;								// 트리거 범위 0~255
const DWORD MAX_CONTROLLERS = 4;										

// state.Gamepad.wButtons에서 게임 패드 버튼에 해당하는 비트
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
    XINPUT_VIBRATION    vibration;			// 진동
    float               vibrateTimeLeft;    // 밀리초
    float               vibrateTimeRight;   
    bool                connected;
};

class Input
{
private:
    bool keysDown[inputNS::KEYS_ARRAY_LEN];     // 특정 키를 누른 경우 true가 되는 배열 
	bool keysUp[inputNS::KEYS_ARRAY_LEN];     // 특정 키를 뗀 경우 true가 되는 배열 
    bool keysPressed[inputNS::KEYS_ARRAY_LEN];  // 게임 루프가 동작하는 동안 특정 키를 누른 경우 true가 되는 배열 
    std::string textIn;                         // 사용자가 입력한 텍스트
    char charIn;                                // 마지막에 입력한 문자
    bool newLine;                               // 새로운 줄을 시작할 때 true가 된다.
    int  mouseX, mouseY;                        // 화면 위의 마우스 위치
    int  mouseRawX, mouseRawY;                  // 정밀 마우스 데이터
    RAWINPUTDEVICE Rid[1];                      // 정밀 마우스용
    bool mouseCaptured;                         // 마우스가 캡쳐된 경우 true가 됨
    bool mouseLButton;                          // 마우스 왼쪽 버튼을 누른 경우 true가 됨
    bool mouseMButton;                          // 마우스 가운데 버튼을 누른 경우 true가 됨
    bool mouseRButton;                          // 마우스 오른쪽 버튼을 누른 경우 true가 됨
    bool mouseX1Button;                         // 마우스 X1 버튼을 누른 경우 true가 됨
    bool mouseX2Button;                         // 마우스 X2쪽 버튼을 누른 경우 true가 됨
    ControllerState controllers[MAX_CONTROLLERS];    // 컨트롤러 상태

public:
    Input(); // 생성자
    virtual ~Input(); // 소멸자

    void initialize(HWND hwnd, bool capture); // 입력 초기화

    void keyDown(WPARAM);	// 키 상태 저장
    void keyUp(WPARAM);
    void keyIn(WPARAM);		// textIn에 입력한 문자를 저장

	bool isKeyUp(UCHAR vkey);			//	
    bool isKeyDown(UCHAR vkey) const;		// 가상키를 눌렀을 경우 true리턴
    bool wasKeyPressed(UCHAR vkey) const;	// 가장 최근 프레임에 특정 가상키를 눌렀을 경우 true반환
    bool anyKeyPressed() const;				// 가장 최근에 아무 키를 눌렀을 경우 true 반환 

    void clearKeyPress(UCHAR vkey);						// 특정 키 입력 정보 클리어
    void clear(UCHAR what);								// 특정 입력버퍼 클리어
    void clearAll() {clear(inputNS::KEYS_MOUSE_TEXT);}	// 모든 입력 정보 클리어
    void clearTextIn() {textIn.clear();}				// 입력된 텍스트 클리어

    std::string getTextIn() {return textIn;} // 입력한 텍스트를 string으로 변환
    char getCharIn()        {return charIn;} // 마지막에 입력한 문자를 반환

    void mouseIn(LPARAM);		// 마우스 좌표값을 mouseX, mouseY에 저장
    void mouseRawIn(LPARAM);	// 정밀 마우스 좌표값을 mouseRawX, mouseRawY에 저장

	//---- 마우스 버튼 상태 저장 ----//
    void setMouseLButton(bool b) { mouseLButton = b; } 
    void setMouseMButton(bool b) { mouseMButton = b; } 
    void setMouseRButton(bool b) { mouseRButton = b; } 
    void setMouseXButton(WPARAM wParam) {mouseX1Button = (wParam & MK_XBUTTON1) ? true:false;
                                         mouseX2Button = (wParam & MK_XBUTTON2) ? true:false;}
    //-------------------------------//

	// 마우스 위치값 반환
    int  getMouseX()        const { return mouseX; }
    int  getMouseY()        const { return mouseY; }

	// 정밀 마우스 위치값 반환
    int  getMouseRawX()     const { return mouseRawX; }
    int  getMouseRawY()     const { return mouseRawY; }

    // 버튼 상태 반환
    bool getMouseLButton()  const { return mouseLButton; }
    bool getMouseMButton()  const { return mouseMButton; }
    bool getMouseRButton()  const { return mouseRButton; }
    bool getMouseX1Button() const { return mouseX1Button; }
    bool getMouseX2Button() const { return mouseX2Button; }

	
    void checkControllers();	// 컨트롤러 체크
    void readControllers();		// 컨트롤러 읽어옴

	// 지정된 컨트롤러의 상태를 반환한다.
    const ControllerState* getControllerState(UINT n)
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return &controllers[n];
    }

    // 컨트롤러 n의 버튼 상태를 반환한다.
    const WORD getGamepadButtons(UINT n)
    {
        if(n > MAX_CONTROLLERS-1)
            n=MAX_CONTROLLERS-1;
        return controllers[n].state.Gamepad.wButtons;
    }

	//----- 컨트롤러 버튼 상태 반환 -----//
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

    // 컨트롤러의 아날로그 컨트롤러 상태 반환 //
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

	// 컨트롤러 진동 효과, 속도 0 = 사용안함, 65535 = 100%, sec은 진동할 초 단위 시간
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

    void vibrateControllers(float frameTime); // 컨트롤러 진동 효과
};

#endif

