#ifndef _ENTITY_H              
#define _ENTITY_H
#define WIN32_LEAN_AND_MEAN

#include "Junk2DSprite.h"
#include "input.h"
#include "game.h"

namespace entityNS
{
    enum COLLISION_TYPE {NONE, CIRCLE, BOX, ROTATED_BOX};
    const float GRAVITY = 6.67428e-11f;         // �߷°�
}

class Entity : public Junk2DSprite
{
  protected:
    entityNS::COLLISION_TYPE collisionType;
    VECTOR2 center;         // ��ƼƼ�� �߽�
    float   radius;         
    VECTOR2 distSquared;    // ���� �浹ü�� ����� ���
    float   sumRadiiSquared;
    RECT    edge;           // �浹ü ������ �𼭸�
    VECTOR2 corners[4];     // for ROTATED_BOX collision detection
    VECTOR2 edge01,edge03;  // edges used for projection
    float   edge01Min, edge01Max, edge03Min, edge03Max; // ������
    VECTOR2 velocity;       // velocity
    VECTOR2 deltaV;         // added to velocity during next call to update()
    float   mass;           // ����
    float   rr;             // Radius squared variable
    float   force;          // �߷��� ��
    float   gravity;        // �߷�
    Input   *input;         // ��ǲ�ý����� ������
    HRESULT hr;             // standard return type
    bool    active;         // Ȱ��ȭ ����
    bool    rotatedBoxReady;// true when rotated collision box is ready
	bool	isTrigger;		// �浹ü ����
    
	// Separating axis collision detection helper functions
    void computeRotatedBox();
    bool projectionsOverlap(Entity &ent);
    bool collideCornerCircle(VECTOR2 corner, Entity &ent);

  public:
    // ������/�Ҹ���
    Entity();
    virtual ~Entity() {}

	std::string collisionTag;

	// ���� �浹
	// Pre: &ent = �ٸ� �浹ü
	// Post: &collisionVector �浹ü�� ����
	virtual bool collideCircle(Entity &ent);
	virtual bool collideBox(Entity &ent);
	// �������ִ� �ڽ� �浹�˻�
	virtual bool collideRotatedBox(Entity &ent);
	virtual bool collideRotatedBoxCircle(Entity &ent);

	// get/set �Լ���

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

	// �浹Ÿ�� ���� (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

    // �浹ü ������Ʈ
    virtual void update(float frameTime);

    // �浹ü 
    // Pre: *gamePtr = ���ӿ�����Ʈ�� ������
    //      width = ���� (0�� ��� �ִ밪)
    //      height = ���� (0�� ��� �ִ밪)
    //      ncols = �ؽ�ó ���� ���� (0 = 1)
    virtual void initialize(Graphics *g, const char * filename, int width, int height, int ncols);
    // Ȱ��ȭ
    virtual void activate();
	/*
	virtual void setXY(float newX, float newY) { 
		center.x = newX;	  center.y = newY;
		spriteData.x = newX;  spriteData.y = newY; 
	}*/

    virtual void ai(float frameTime, Entity &ent);

    // �簢���� �ٱ�
    virtual bool outsideRect(RECT rect);

    // �� �浹ü�� �ٸ� �浹ü�� �浹�ߴ°�
    virtual bool collidesWith(Entity &ent);

	// �浹ü�� �Դ� ������
    virtual void damage(int weapon);

	// �ٿ
    void bounce(VECTOR2 &collisionVector, Entity &ent);

    // �߷� ����
    void gravityForce(Entity *other, float frameTime);
};

#endif
