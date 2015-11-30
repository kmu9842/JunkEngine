#include "..\\Headers\\input.h"

Input::Input() // ����Ʈ ������
{
	//-- Ű �迭 �ʱ�ȭ --//
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysDown[i] = false;
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		keysUp[i] = false;
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysPressed[i] = false;
	//--------------------//

    newLine = true;                     // ���ο� �� ����
    textIn = "";                        // textIn �ʱ�ȭ
    charIn = 0;                         // charIn �ʱ�ȭ

    // mouse data
    mouseX = 0;                         // X ��ġ
    mouseY = 0;                         // Y ��ġ
    mouseRawX = 0;                      // ���� ���콺�� X ��ġ
    mouseRawY = 0;                      // ���� ���콺�� Y ��ġ
    mouseLButton = false;               // ���콺 ���� ��ư�� ������� true
    mouseMButton = false;               // ���콺 ��� ��ư�� ������� true
    mouseRButton = false;               // ���콺 ������ ��ư�� ������� true
    mouseX1Button = false;              // ���콺 X1 ��ư�� ������� true
    mouseX2Button = false;              // ���콺 X2 ��ư�� ������� true

    for(int i=0; i<MAX_CONTROLLERS; i++)
    {
        controllers[i].vibrateTimeLeft = 0;
        controllers[i].vibrateTimeRight = 0;
    }
}

Input::~Input() // �Ҹ���
{
    if(mouseCaptured)
        ReleaseCapture();               // ���콺 ����
}

void Input::initialize(HWND hwnd, bool capture) // ���콺 �ʱ�ȭ, ���콺�� ĸ���ϴµ� ������ true�� ��ȯ
{
    try{
        mouseCaptured = capture;

        // ���� ���콺�� ���
        Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
        Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
        Rid[0].dwFlags = RIDEV_INPUTSINK;   
        Rid[0].hwndTarget = hwnd;
        RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

        if(mouseCaptured)
            SetCapture(hwnd);           // ���콺 ĸ��

        ZeroMemory( controllers, sizeof(ControllerState) * MAX_CONTROLLERS ); // ��Ʈ�ѷ� ���¸� ����

        checkControllers();             // ����� ��Ʈ�ѷ� Ȯ��
    }
    catch(...)
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
    }
}

void Input::keyDown(WPARAM wParam) // �ش� Ű�� ���� keysDown�� keyPress �迭�� true�� ����
{
    if (wParam < inputNS::KEYS_ARRAY_LEN) // Ű �ڵ尡 ���� �����ȿ� �ִ��� Ȯ�� 
    {
        keysDown[wParam] = true;    // �迭 ����
        //keysPressed[wParam] = true; 
    }
}

void Input::keyUp(WPARAM wParam) // �ش� Ű�� ���� keysDown �迭�� false�� ����
{
	if (wParam < inputNS::KEYS_ARRAY_LEN) {
		keysDown[wParam] = false;
		keysUp[wParam] = true;
	}
}

void Input::keyIn(WPARAM wParam) // textIn�� �Է��� ���ڸ� ����
{
    if (newLine)                            // �� ���� �����ϰ��
    {
        textIn.clear();
        newLine = false;
    }

    if (wParam == '\b')                     // �齺���̽��� ���
    {
        if(textIn.length() > 0)             // ���ڰ� ������ ���
            textIn.erase(textIn.size()-1);  // ������ ���ڸ� ����
    }
    else
    {
        textIn += wParam;                   // ���ڸ� �Է���
        charIn = wParam;                    // �������� �Է��� ���ڸ� ����
    }

    if ((char)wParam == '\r')               // �� ����� ���ð��   
        newLine = true;                     // ���ο� �� ����
}

bool Input::isKeyDown(UCHAR vkey) const // ����Ű�� ������ ��� true����
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        return keysDown[vkey];
    else
        return false;
}

bool Input::isKeyUp(UCHAR vkey) // ����Ű�� ������ ��� true����
{
	if (vkey < inputNS::KEYS_ARRAY_LEN){
		bool a = keysUp[vkey];
		keysUp[vkey] = false;
		return a;
	}
	else
		return false;
}

bool Input::wasKeyPressed(UCHAR vkey) const // ���� �ֱ� �����ӿ� Ư�� ����Ű�� ������ ��� true��ȯ
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        return keysPressed[vkey];
    else
        return false;
}

bool Input::anyKeyPressed() const // ���� �ֱٿ� �ƹ� Ű�� ������ ��� true ��ȯ
{
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        if(keysPressed[i] == true)
            return true;
    return false;
}

void Input::clearKeyPress(UCHAR vkey) // Ư�� Ű �Է� ���� Ŭ����
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        keysPressed[vkey] = false;
}

void Input::clear(UCHAR what) // Ư�� �Է¹��� Ŭ����
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

void Input::mouseIn(LPARAM lParam) // ���콺 ��ǥ�� ����
{
    mouseX = GET_X_LPARAM(lParam); 
    mouseY = GET_Y_LPARAM(lParam);
}

void Input::mouseRawIn(LPARAM lParam) // ���� ���콺 ��ǥ���� mouseRawX, mouseRawY�� ����
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

void Input::checkControllers() // ��Ʈ�ѷ� üũ
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

void Input::readControllers() // ��Ʈ�ѷ� �о����
{
    DWORD result;
    for( DWORD i = 0; i <MAX_CONTROLLERS; i++)
    {
        if(controllers[i].connected)
        {
            result = XInputGetState(i, &controllers[i].state);
            if(result == ERROR_DEVICE_NOT_CONNECTED)    // ������ ���� ���� ���
                controllers[i].connected = false;
        }
    }
}

void Input::vibrateControllers(float frameTime) // ��Ʈ�ѷ� ����
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
