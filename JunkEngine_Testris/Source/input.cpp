#include "..\\Headers\\input.h"

Input::Input() // 디폴트 생성자
{
	//-- 키 배열 초기화 --//
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysDown[i] = false;
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysUp[i] = false;
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysPressed[i] = false;
	//--------------------//

    newLine = true;                     // 새로운 줄 시작
    textIn = "";                        // textIn 초기화
    charIn = 0;                         // charIn 초기화

    // mouse data
    mouseX = 0;                         // X 위치
    mouseY = 0;                         // Y 위치
    mouseRawX = 0;                      // 정밀 마우스의 X 위치
    mouseRawY = 0;                      // 정밀 마우스의 Y 위치
    mouseLButton = false;               // 마우스 왼쪽 버튼을 누를경우 true
    mouseMButton = false;               // 마우스 가운데 버튼을 누를경우 true
    mouseRButton = false;               // 마우스 오른쪽 버튼을 누를경우 true
    mouseX1Button = false;              // 마우스 X1 버튼을 누를경우 true
    mouseX2Button = false;              // 마우스 X2 버튼을 누를경우 true

    for(int i=0; i<MAX_CONTROLLERS; i++)
    {
        controllers[i].vibrateTimeLeft = 0;
        controllers[i].vibrateTimeRight = 0;
    }
}

Input::~Input() // 소멸자
{
    if(mouseCaptured)
        ReleaseCapture();               // 마우스 해제
}

void Input::initialize(HWND hwnd, bool capture) // 마우스 초기화, 마우스를 캡쳐하는데 성공시 true값 반환
{
    try{
        mouseCaptured = capture;

        // 정밀 마우스를 등록
        Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
        Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
        Rid[0].dwFlags = RIDEV_INPUTSINK;   
        Rid[0].hwndTarget = hwnd;
        RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

        if(mouseCaptured)
            SetCapture(hwnd);           // 마우스 캡쳐

        ZeroMemory( controllers, sizeof(ControllerState) * MAX_CONTROLLERS ); // 컨트롤러 상태를 지움

        checkControllers();             // 연결된 컨트롤러 확인
    }
    catch(...)
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
    }
}

void Input::keyDown(WPARAM wParam) // 해당 키에 대해 keysDown과 keyPress 배열을 true로 설정
{
    if (wParam < inputNS::KEYS_ARRAY_LEN) // 키 코드가 버퍼 범위안에 있는지 확인 
    {
        keysDown[wParam] = true;    // 배열 갱신
        //keysPressed[wParam] = true; 
    }
}

void Input::keyUp(WPARAM wParam) // 해당 키에 대해 keysDown 배열을 false로 설정
{
	if (wParam < inputNS::KEYS_ARRAY_LEN) {
		keysDown[wParam] = false;
		keysUp[wParam] = true;
	}
}

void Input::keyIn(WPARAM wParam) // textIn에 입력한 문자를 저장
{
    if (newLine)                            // 새 줄의 시작일경우
    {
        textIn.clear();
        newLine = false;
    }

    if (wParam == '\b')                     // 백스페이스일 경우
    {
        if(textIn.length() > 0)             // 문자가 존재할 경우
            textIn.erase(textIn.size()-1);  // 마지막 문자를 지움
    }
    else
    {
        textIn += wParam;                   // 문자를 입력함
        charIn = wParam;                    // 마지막에 입력한 문자를 저장
    }

    if ((char)wParam == '\r')               // 줄 띄움이 들어올경우   
        newLine = true;                     // 새로운 줄 시작
}

bool Input::isKeyDown(UCHAR vkey) const // 가상키를 눌렀을 경우 true리턴
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        return keysDown[vkey];
    else
        return false;
}

bool Input::isKeyUp(UCHAR vkey) // 가상키를 눌렀을 경우 true리턴
{
	if (vkey < inputNS::KEYS_ARRAY_LEN){
		bool a = keysUp[vkey];
		keysUp[vkey] = false;
		return a;
	}
	else
		return false;
}

bool Input::wasKeyPressed(UCHAR vkey) const // 가장 최근 프레임에 특정 가상키를 눌렀을 경우 true반환
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        return keysPressed[vkey];
    else
        return false;
}

bool Input::anyKeyPressed() const // 가장 최근에 아무 키를 눌렀을 경우 true 반환
{
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        if(keysPressed[i] == true)
            return true;
    return false;
}

void Input::clearKeyPress(UCHAR vkey) // 특정 키 입력 정보 클리어
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        keysPressed[vkey] = false;
}

void Input::clear(UCHAR what) // 특정 입력버퍼 클리어
{
    if(what & inputNS::KEYS_DOWN)       
    {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            keysDown[i] = false;
    }
    if(what & inputNS::KEYS_PRESSED)    
    {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            keysPressed[i] = false;
    }
    if(what & inputNS::MOUSE)           
    {
        mouseX = 0;
        mouseY = 0;
        mouseRawX = 0;
        mouseRawY = 0;
    }
    if(what & inputNS::TEXT_IN)
        clearTextIn();
}

void Input::mouseIn(LPARAM lParam) // 마우스 좌표값 저장
{
    mouseX = GET_X_LPARAM(lParam); 
    mouseY = GET_Y_LPARAM(lParam);
}

void Input::mouseRawIn(LPARAM lParam) // 정밀 마우스 좌표값을 mouseRawX, mouseRawY에 저장
{
    UINT dwSize = 40;
    static BYTE lpb[40];
    
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, 
                    lpb, &dwSize, sizeof(RAWINPUTHEADER));
    
    RAWINPUT* raw = (RAWINPUT*)lpb;
    
    if (raw->header.dwType == RIM_TYPEMOUSE) 
    {
        mouseRawX = raw->data.mouse.lLastX;
        mouseRawY = raw->data.mouse.lLastY;
    } 
}

void Input::checkControllers() // 컨트롤러 체크
{
    DWORD result;
    for( DWORD i = 0; i <MAX_CONTROLLERS; i++)
    {
        result = XInputGetState(i, &controllers[i].state);
        if(result == ERROR_SUCCESS)
            controllers[i].connected = true;
        else
            controllers[i].connected = false;
    }
}

void Input::readControllers() // 컨트롤러 읽어오기
{
    DWORD result;
    for( DWORD i = 0; i <MAX_CONTROLLERS; i++)
    {
        if(controllers[i].connected)
        {
            result = XInputGetState(i, &controllers[i].state);
            if(result == ERROR_DEVICE_NOT_CONNECTED)    // 연결이 끊어 졌을 경우
                controllers[i].connected = false;
        }
    }
}

void Input::vibrateControllers(float frameTime) // 컨트롤러 진동
{
    for(int i=0; i < MAX_CONTROLLERS; i++)
    {
        if(controllers[i].connected)
        {
            controllers[i].vibrateTimeLeft -= frameTime;
            if(controllers[i].vibrateTimeLeft < 0)
            {
                controllers[i].vibrateTimeLeft = 0;
                controllers[i].vibration.wLeftMotorSpeed = 0;
            }
            controllers[i].vibrateTimeRight -= frameTime;
            if(controllers[i].vibrateTimeRight < 0)
            {
                controllers[i].vibrateTimeRight = 0;
                controllers[i].vibration.wRightMotorSpeed = 0;
            }
            XInputSetState(i, &controllers[i].vibration);
        }
    }
}
