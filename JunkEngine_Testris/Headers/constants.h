#ifndef _CONSTANTS_H            
#define _CONSTANTS_H            
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <windows.h>

#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255) 

//-------- 매크로들 --------//
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }

//-----------------------------------------------
//                  상수들
//-----------------------------------------------

// 윈도우
const char CLASS_NAME[] = "ExampleGame";
const char GAME_TITLE[] = "ExampleGame";
const bool FULLSCREEN = false;
const UINT GAME_WIDTH = 960;
const UINT GAME_HEIGHT = 720;

// 게임
const double PI = 3.14159265;
const float FRAME_RATE = 60.0f;
const float MIN_FRAME_RATE = 10.0f;
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;

// 키 맵핑
const UCHAR ESC_KEY = VK_ESCAPE;   // esc키
const UCHAR ALT_KEY = VK_MENU;     // Alt키
const UCHAR ENTER_KEY = VK_RETURN;   // 엔터키

// 플레이어 어빌리티
const UINT PlayerAbility = 4;

const UINT MapXY = 300;

enum class direction {
	right, left, up, down
};
enum class shapeSet {
	_I,   // 체고 조넘
	_L,   // L 자형
	_4,   // 정사각형
	_22R, // 아래쪽이 내려간 22블록
	_22L, // 왼쪽이 내려간 22블록
	_Y    // ㅓ자형 블록
};

#endif
