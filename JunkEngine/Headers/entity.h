#ifndef _ENTITY_H              
#define _ENTITY_H
#define WIN32_LEAN_AND_MEAN

#include "Junk2DSprite.h"
#include "input.h"
#include "game.h"

namespace entityNS
{
    enum COLLISION_TYPE {NONE, CIRCLE, BOX, ROTATED_BOX};
    const float GRAVITY = 6.67428e-11f;         // 중력값
}

class Entity : public Junk2DSprite
{
  protected:
    entityNS::COLLISION_TYPE collisionType;
    VECTOR2 center;         // 엔티티의 중심
    float   radius;         
    VECTOR2 distSquared;    // 원형 충돌체를 사용할 경우
    float   sumRadiiSquared;
    RECT    edge;           // 충돌체 상자의 모서리
    VECTOR2 corners[4];     // for ROTATED_BOX collision detection
    VECTOR2 edge01,edge03;  // edges used for projection
    float   edge01Min, edge01Max, edge03Min, edge03Max; // 꼭지점
    VECTOR2 velocity;       // velocity
    VECTOR2 deltaV;         // added to velocity during next call to update()
    float   mass;           // 무게
    float   rr;             // Radius squared variable
    float   force;          // 중력의 힘
    float   gravity;        // 중력
    Input   *input;         // 인풋시스템의 포인터
    HRESULT hr;             // standard return type
    bool    active;         // 활성화 여부
    bool    rotatedBoxReady;// true when rotated collision box is ready
	bool	isTrigger;		// 충돌체 여부
    
	// Separating axis collision detection helper functions
    void computeRotatedBox();
    bool projectionsOverlap(Entity &ent);
    bool collideCornerCircle(VECTOR2 corner, Entity &ent);

  public:
    // 생성자/소멸자
    Entity();
    virtual ~Entity() {}

	std::string collisionTag;

	// 원형 충돌
	// Pre: &ent = 다른 충돌체
	// Post: &collisionVector 충돌체의 백터
	virtual bool collideCircle(Entity &ent);
	virtual bool collideBox(Entity &ent);
	// 돌려져있는 박스 충돌검사
	virtual bool collideRotatedBox(Entity &ent);
	virtual bool collideRotatedBoxCircle(Entity &ent);

	// get/set 함수들

    virtual const VECTOR2* getCenter()   
    {
        center = VECTOR2(getCenterX(),getCenterY());
        return &center;
    }
    virtual float getRadius() const     {return radius;}
    virtual const RECT& getEdge() const {return edge;}
    virtual const VECTOR2* getCorner(UINT c) const
    {
        if(c>=4) 
            c=0;
        return &corners[c]; 
    }
	
    virtual const VECTOR2 getVelocity() const {return velocity;}
    virtual bool  getActive()         const {return active;}
    virtual float getMass()           const {return mass;}
    virtual float getGravity()        const {return gravity;}

	virtual void  setCollisionType(entityNS::COLLISION_TYPE c) 
											{ collisionType = c; }
    virtual void  setVelocity(VECTOR2 v)    {velocity = v;}
    virtual void  setDeltaV(VECTOR2 dv)     {deltaV = dv;}
    virtual void  setActive(bool a)         {active = a;}
    virtual void  setMass(float m)          {mass = m;}
    virtual void  setGravity(float g)       {gravity = g;}
    virtual void setCollisionRadius(float r)    {radius = r;}

	// 충돌타입 리턴 (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

    // 충돌체 업데이트
    virtual void update(float frameTime);

    // 충돌체 
    // Pre: *gamePtr = 게임오브젝트의 포인터
    //      width = 가로 (0일 경우 최대값)
    //      height = 세로 (0일 경우 최대값)
    //      ncols = 텍스처 분할 개수 (0 = 1)
    virtual void initialize(Graphics *g, const char * filename, int width, int height, int ncols);
    // 활성화
    virtual void activate();
	/*
	virtual void setXY(float newX, float newY) { 
		center.x = newX;	  center.y = newY;
		spriteData.x = newX;  spriteData.y = newY; 
	}*/

    virtual void ai(float frameTime, Entity &ent);

    // 사각형의 바깥
    virtual bool outsideRect(RECT rect);

    // 이 충돌체가 다른 충돌체와 충돌했는가
    virtual bool collidesWith(Entity &ent);

	// 충돌체가 입는 데미지
    virtual void damage(int weapon);

	// 바운스
    void bounce(VECTOR2 &collisionVector, Entity &ent);

    // 중력 적용
    void gravityForce(Entity *other, float frameTime);
};

#endif
