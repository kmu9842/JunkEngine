#include "..\\Headers\\game.h"

Game::Game()
{
    input = new Input();        // 키보드 입력 초기화 이후 Ipnut클래스에서 추가 초기화
    paused = false;             
    graphics = NULL;
    initialized = false;
}

Game::~Game()
{
    deleteAll();                // 메모리 해제
    ShowCursor(true);           // 커서 표시
}

LRESULT Game::messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) // 윈도우 메세지 헨들러
{
    if(initialized)     // 초기화 됐을 경우에만 처리
    {
        switch( msg )
        {

			// 윈도우 핸들러 코드를 Input클라스로 전달

            case WM_DESTROY:
                PostQuitMessage(0);        // 종료
                return 0;
            case WM_KEYDOWN: case WM_SYSKEYDOWN:    // 키 누름
                input->keyDown(wParam);
                return 0;
            case WM_KEYUP: case WM_SYSKEYUP:        // 키 뗌
                input->keyUp(wParam);
                return 0;
            case WM_CHAR:                           // 문자입력
                input->keyIn(wParam);
                return 0;
            case WM_MOUSEMOVE:                      // 마우스 움직임
                input->mouseIn(lParam);
                return 0;
            case WM_INPUT:                          // 마우스 데이터가 들어옴
                input->mouseRawIn(lParam);
                return 0;
            case WM_LBUTTONDOWN:                    // 마우스 왼쪽버튼 누름
                input->setMouseLButton(true);
                input->mouseIn(lParam);             // 마우스 위치
                return 0;
            case WM_LBUTTONUP:                      // 마우스 왼쪽버튼 뗌
                input->setMouseLButton(false);
                input->mouseIn(lParam);             
                return 0;
            case WM_MBUTTONDOWN:                    // 마우스 가운데 버튼 누름
                input->setMouseMButton(true);
                input->mouseIn(lParam);             
                return 0;
            case WM_MBUTTONUP:                      // 마우스 가운데 버튼 뗌
                input->setMouseMButton(false);
                input->mouseIn(lParam);             
                return 0;
            case WM_RBUTTONDOWN:                    // 마우스 오른쪽 버튼 누름
                input->setMouseRButton(true);
                input->mouseIn(lParam);             
                return 0;
            case WM_RBUTTONUP:                      // 마우스 오른쪽 버튼 뗌
                input->setMouseRButton(false);
                input->mouseIn(lParam);             
                return 0;
            case WM_DEVICECHANGE:                   // 콘트롤러 확인
                input->checkControllers();
                return 0;
        }
    }
    return DefWindowProc( hwnd, msg, wParam, lParam );    // 윈도우가 처리하게 함
}

// 게임 초기화
void Game::initialize(HWND hw)
{
    hwnd = hw;                                  // 윈도우 핸들 저장
   
    graphics = new Graphics();											// 그래픽 객체 초기화
    graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);	// 게임 에러를 뱉는다

    // Input객체 초기화
    input->initialize(hwnd, false);            

    // 타이머 사용
    if(QueryPerformanceFrequency(&timerFreq) == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

    QueryPerformanceCounter(&timeStart);        // 시작 시간 가져오기

    initialized = true;
}

// 게임 렌더링
void Game::renderGame()
{
    if (SUCCEEDED(graphics->beginScene()))
    {
        render();               // 파생클래스에서 render를 호출
        graphics->endScene();	// 렌더링을 멈춘다
    }

    handleLostGraphicsDevice();

    graphics->showBackbuffer(); // 백 버퍼 표시
}

// 로스트 상태의 그래픽 디바이스 처리
void Game::handleLostGraphicsDevice()
{
    hr = graphics->getDeviceState(); // 로스트 상태의 디바이스를 테스트 한 뒤 처리
    if(FAILED(hr))                   
    {
        if(hr == D3DERR_DEVICELOST) // 디바이스가 로스트 상태이며 리셋이 불가능 할경우 CPU에게 시간을 양보
        {
            Sleep(100);             
            return;
        } 

        else if(hr == D3DERR_DEVICENOTRESET) 
        {
            releaseAll();
            hr = graphics->reset(); 
            if(FAILED(hr))          
                return;
            resetAll();
        }
        else
            return;                 // 다른 장치의 에러임을 확인시켜준다
    }
}

void Game::run(HWND hwnd)
{
    if(graphics == NULL)            
        return;

	// 프레임 레이트 계산
    QueryPerformanceCounter(&timeEnd);
    frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart ) / 
                (float)timerFreq.QuadPart;

	// 절전 코드, Winnm.lib 필요
    if (frameTime < MIN_FRAME_TIME) 
    {
        sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime)*1000);
        timeBeginPeriod(1);         
        Sleep(sleepTime);           // cpu를 쉬게한다.
        timeEndPeriod(1);           
        return;
    }

    if (frameTime > 0.0)
        fps = (fps*0.99f) + (0.01f/frameTime);  // 평균 FPS

    if (frameTime > MAX_FRAME_TIME) // 프레임 속도가 느릴경우 최대 frameTime으로 제한
        frameTime = MAX_FRAME_TIME; // 최대 frameTime으로 제한

    timeStart = timeEnd;

    if (!paused)                    
    {
        update();                   // 모든 게임요소 갱신
		UpdateEntity();				// 오브젝트들의 충돌 검사
        input->vibrateControllers(frameTime); // 컨트롤러 진동처리
    }
    renderGame();                   // 모든 요소 렌더링
    input->readControllers();       // 컨트롤러의 상태 읽기

    input->clear(inputNS::KEYS_PRESSED); // 입력된것 초기화

	//system("CLS");
	//printf("%.1f\n", fps);
}

void Game::addEntity(Junk2DEntity* entity) {
	ObjectsEntity.push_back(entity);
}

void Game::UpdateEntity()
{
	for (auto i : ObjectsEntity) {
		for (auto j : ObjectsEntity) {
			if (i != j) {
				i->collidesWith(*j);
			}
		}
	}

	for (auto i : ObjectsEntity) {
		i->update(frameTime);
	}
}

void Game::releaseAll()
{}

void Game::resetAll()
{}

void Game::deleteAll()
{
    releaseAll();               
    SAFE_DELETE(graphics);
    SAFE_DELETE(input);
    initialized = false;
}