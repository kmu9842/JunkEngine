#include "..\\Headers\\image.h"

// 생성자, 소멸자
Image::Image()
{
    initialized = false;            // set true when successfully initialized
    spriteData.width = 2;
    spriteData.height = 2;
    spriteData.x = 0.0;
    spriteData.y = 0.0;
    spriteData.scale = 1.0;
    spriteData.angle = 0.0;
    spriteData.rect.left = 0;       // used to select one frame from multi-frame image
    spriteData.rect.top = 0;
    spriteData.rect.right = spriteData.width;
    spriteData.rect.bottom = spriteData.height;
    spriteData.texture = NULL;      // the sprite texture (picture)
    spriteData.flipHorizontal = false;
    spriteData.flipVertical = false;
    cols = 1;
    textureManager = NULL;
    startFrame = 0;
    endFrame = 0;
    currentFrame = 0;
    frameDelay = 1.0;               // default to 1 second per frame of animation
    animTimer = 0.0;
    visible = true;                 // the image is visible
    loop = true;                    // loop frames
    animComplete = false;
    graphics = NULL;                // link to graphics system
    colorFilter = graphicsNS::WHITE; // WHITE for no change
}
Image::~Image()
{}

//=============================================================================
// Image 객체 초기화
// 성공하면 true, 실패하면 false 반환
// Graphics를 가리키는 포인터
// 이미지의 픽셀 단위 폭, 높이, 텍스처의 행 수(1 ~ n)
// TextureManager를 가리키는 포인터
//=============================================================================
bool Image::initialize(Graphics *g, int width, int height, int ncols,
                       TextureManager *textureM)
{
    try{
        graphics = g;                               // graphics 객체
        textureManager = textureM;                  // 텍스처 객체를 가리키는 포인터

        spriteData.texture = textureManager->getTexture();
        if(width == 0)
            width = textureManager->getWidth();     // 전체 폭 사용
        spriteData.width = width;
        if(height == 0)
            height = textureManager->getHeight();   // 전체 높이 사용
        spriteData.height = height;
        cols = ncols;
        if (cols == 0)
            cols = 1;                               // cols가 0일 경우 1을 사용

        // currentFrame을 그리기 위해 spriteData.rect를 구성
        spriteData.rect.left = (currentFrame % cols) * spriteData.width;
        // 오른쪽 모서리 + 1
        spriteData.rect.right = spriteData.rect.left + spriteData.width;
        spriteData.rect.top = (currentFrame / cols) * spriteData.height;
        // 왼쪽 모서리 + 1
        spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
    }
    catch(...) {
		return false;
	}

    initialized = true;                                
    return true;
}


//=============================================================================
// color를 필터로 사용하여 이미지를 그림
// 이전에 spriteBegin()이 호출 되며,
// 이후 spriteEnd() 이 호출 된다.
//=============================================================================
void Image::draw(COLOR_ARGB color)
{
    if (!visible || graphics == NULL)
        return;
    // onReset()이 호출될 경우를 대비해 새로운 텍스처를 가져옴
    spriteData.texture = textureManager->getTexture();
    if(color == graphicsNS::FILTER)                     // 필터를 사용하여 그리는 경우
        graphics->drawSprite(spriteData, colorFilter);  // colorFilter 사용
    else
        graphics->drawSprite(spriteData, color);        // color를 필터로 사용
}

//=============================================================================
// 지정한 SpriteData를 사용하여 이미지를 그림
//   SpriteData.rect는 텍스처를 선택하는 데 사용
// 이전에 spriteBegin()이 호출 되며,
// 이후 spriteEnd() 이 호출 된다.
//=============================================================================
void Image::draw(SpriteData sd, COLOR_ARGB color)
{
    if (!visible || graphics == NULL)
        return;
    sd.rect = spriteData.rect;                  // 텍스처를 선택하기 위해 이미지의 rect를 사용
	// onReset()이 호출될 경우를 대비해 새로운 텍스처를 가져옴
	sd.texture = textureManager->getTexture();  

    if(color == graphicsNS::FILTER)             // 필터를 사용하여 그리는 경우
        graphics->drawSprite(sd, colorFilter);  // colorFilter 사용
    else
        graphics->drawSprite(sd, color);        // color를 필터로 사용
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Image::update(float frameTime)
{
    if (endFrame - startFrame > 0)          // if animated sprite
    {
        animTimer += frameTime;             // total elapsed time
        if (animTimer > frameDelay)
        {
            animTimer -= frameDelay;
            currentFrame++;
            if (currentFrame < startFrame || currentFrame > endFrame)
            {
                if(loop == true)            // if looping animation
                    currentFrame = startFrame;
                else                        // not looping animation
                {
                    currentFrame = endFrame;
                    animComplete = true;    // animation complete
                }
            }
            setRect();                      // set spriteData.rect
        }
    }
}

void Image::setCurrentFrame(int c) 
{
    if(c >= 0)
    {
        currentFrame = c;
        animComplete = false;
        setRect();                          // set spriteData.rect
    }
}

inline void Image::setRect() 
{
    // configure spriteData.rect to draw currentFrame
    spriteData.rect.left = (currentFrame % cols) * spriteData.width;
    // right edge + 1
    spriteData.rect.right = spriteData.rect.left + spriteData.width;
    spriteData.rect.top = (currentFrame / cols) * spriteData.height;
    // bottom edge + 1
    spriteData.rect.bottom = spriteData.rect.top + spriteData.height;       
}

