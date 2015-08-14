#ifndef _GAME_H                 // 다중정의 방지
#define _GAME_H                 
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <windows.h>
#include <Mmsystem.h>
#include <fstream>
#include "Junk2Dentity.h"
#include "constants.h"
#include "gameError.h"

class Game
{
protected:
	std::vector<Junk2DEntity*> ObjectsEntity;	// 충돌 요소들을 관리하는 배열
	std::vector<Junk2DEntity> MapsEntity;		// 지형 충돌 요소들을 관리하는 배열 (추후 다른 엔티티로 대체 예정)

	// 공통 속성
	Graphics *graphics;         // Graphics 객체 포인터
	Input   *input;             // Input 객체 포인터
	HWND    hwnd;               // 윈도우 핸들
	HRESULT hr;                 // 표준 반환 타입
	LARGE_INTEGER timeStart;    // 성능 카운터 시작값
	LARGE_INTEGER timeEnd;      // 성능 카운터 종료 값
	LARGE_INTEGER timerFreq;    // 성능 카운터 빈도수
	float   frameTime;          // 마지막 프레임에 필요한 시간
	float   fps;                // 초당 프레임수
	DWORD   sleepTime;          // 프레임 사이의 대기 단위 시간
	bool    paused;             // 게임 일시정지 상태
	bool    initialized;        // 초기화

	int Maps[1000][1000];
	int mapMaxX, mapMaxY;
	

public:
	Game(); // 생성자
	virtual ~Game(); // 소멸자

					 // --------- 멤버 함수 ---------//

					 //윈도우 메세지 핸들러
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// 게임 초기화
	virtual void initialize(HWND hwnd); // hwnd는 윈도우 핸들러
	virtual void run(HWND);				// 반복 호출, 명령 실행
	virtual void releaseAll();          // 그래픽 디바이스 리셋
	virtual void resetAll();			// 표면 재생성 후 모든 개체 리셋
	virtual void deleteAll();           // 예약된 모든 메모리 삭제
	virtual void renderGame();          // 게임 렌더링

	virtual void handleLostGraphicsDevice(); // 로스트 상태가 된 그래픽 디바이스 처리

	Graphics* getGraphics() { return graphics; }	// Graphics 객체 포인터 반환
	Input* getInput() { return input; }		// Input 객체 포인터 반환

	virtual void addEntity(Junk2DEntity* entity);
	virtual void UpdateEntity();

	void exitGame() { // 게임 종료
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	}
	// ------------------------------//

	virtual void mapInput(const char* mapName);
	virtual void LoadMap();

	virtual void update() = 0;		// 게임요소 갱신
	virtual void ai() = 0;			// AI 계산
	virtual void render() = 0;		// 렌더링
};

#endif
