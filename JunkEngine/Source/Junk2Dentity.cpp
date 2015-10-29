#include "..\\Headers\\Junk2Dentity.h"

Junk2DEntity::Junk2DEntity() : Junk2DSprite()
{
    radius = 1.0;
	edge.left = -1;
	edge.top = -1;
	edge.right = 1;
	edge.bottom = 1;
	mass = 1.0;
	velocity.x = 0.0;
	velocity.y = 0.0;
	deltaV.x = 0.0;
	deltaV.y = 0.0;
	active = true;                  // 엔티티 활성화
	rotatedBoxReady = false;
	collisionType = Junk2DentityNS::BOX;
	gravity = Junk2DentityNS::GRAVITY;
	collisionTag = "None";
	isTrigger = false;
	isGravity = false;
	isGround  = false;
	isRigidBody = false;
	isCollid = false;
}

// 충돌체 초기화
void Junk2DEntity::initialize(Graphics *g, const char * filename, int width, int height, int ncols)
{
	Junk2DSprite::settingTexture(g, filename, width, height, ncols);

	center.x = 0.0f;
	center.y = 0.0f;

	edge.left = spriteData.rect.left;
	edge.top = spriteData.rect.top;
	edge.right = spriteData.rect.right;
	edge.bottom = spriteData.rect.bottom;
}

// 충돌체 활성화
void Junk2DEntity::activate()
{
	active = true;
}

// 충돌체 업데이트
void Junk2DEntity::update(float frameTime)
{
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	Junk2DSprite::update(frameTime);
	rotatedBoxReady = false;    // 회전 오프
}

void Junk2DEntity::ai(float frameTime, Junk2DEntity &ent)
{}

// ent와의 충돌 여부
bool Junk2DEntity::collidesWith(Junk2DEntity &ent) {
	// if either Junk2Dentity is not active then no collision may occcur
	if (!active || !ent.getActive())
		return false;
	if (collisionType == Junk2DentityNS::CIRCLE && ent.getCollisionType() == Junk2DentityNS::CIRCLE)
		return collideCircle(ent);
	if (collisionType == Junk2DentityNS::BOX && ent.getCollisionType() == Junk2DentityNS::BOX)
		return collideBox(ent);
	if (collisionType != Junk2DentityNS::CIRCLE && ent.getCollisionType() != Junk2DentityNS::CIRCLE)
		return collideRotatedBox(ent);
	if (collisionType == Junk2DentityNS::CIRCLE)
	{
		bool collide = ent.collideRotatedBoxCircle(*this);
		return collide;
	}
	else
		return collideRotatedBoxCircle(ent);
	return false;
}

// 원형 충돌체끼리의 충돌 여부
bool Junk2DEntity::collideCircle(Junk2DEntity &ent) {
	distSquared = *getCenter() - *ent.getCenter();
	distSquared.x = distSquared.x * distSquared.x;
	distSquared.y = distSquared.y * distSquared.y;

	sumRadiiSquared = (radius*getScale()) + (ent.radius*ent.getScale());
	sumRadiiSquared *= sumRadiiSquared;

	if (distSquared.x + distSquared.y <= sumRadiiSquared)
	{
		return true;
	}
	return false;   // not colliding
}

// 상자형 충돌체끼리의 충돌 여부
bool Junk2DEntity::collideBox(Junk2DEntity &ent)
{
	// 활성 여부
	if (!active || !ent.getActive())
		return false;

	if ((getCenterX() + edge.right*getScale() >= ent.getCenterX() + ent.getEdge().left*ent.getScale()) &&
		(getCenterX() + edge.left*getScale() <= ent.getCenterX() + ent.getEdge().right*ent.getScale()) &&
		(getCenterY() + edge.bottom*getScale() >= ent.getCenterY() + ent.getEdge().top*ent.getScale()) &&
		(getCenterY() + edge.top*getScale() <= ent.getCenterY() + ent.getEdge().bottom*ent.getScale()))
	{
		if (!isTrigger && !ent.getTrigger()) {
			printf("Collider ");
			// 충돌 다시만들어야함
			// 지금 까지는 충돌체 <-> 충돌체 비교후 충돌하면 서로 밀어내도록 만듬
			// 충돌체들이 서로 밀어내도록 만들어 내는 것이 아닌 그 방향으로의 이동을 봉쇄해야함

			//printf("%f\n", getCenterX() + edge.right * getScale());
			//printf("%f\n", ent.getCenterX() + ent.edge.left * ent.getScale());

			int right, left, bottom, top;
			right = getCenterX() + getWidth()/2;
			left = getCenterX() - getWidth()/2;
			top = getCenterY() + getHeight();
			bottom = getCenterY() - getHeight()/2;
			/*
			if (right > ent.getCenterX() + ent.getEdge().left*ent.getScale() &&
				!(top > ent.getCenterY() + ent.getEdge().bottom*ent.getScale()) &&
				!(bottom < ent.getCenterY() + ent.getEdge().top*ent.getScale())) {
				dontMoveRect[0] = 1;
			}*/

			if (right > ent.getCenterX() - ent.getWidth()/2 &&
				bottom < ent.getCenterY() + ent.getHeight() / 2 &&
				top > ent.getCenterY() - ent.getHeight() / 2) {
				dontMoveRect[0] = 1;
				isCollid = true;
			}
			else {
				dontMoveRect[0] = 0;
				isCollid = false;
			}

			if (left < ent.getCenterX() + ent.getWidth() / 2 &&
				bottom < ent.getCenterY() + ent.getHeight() / 2 &&
				top > ent.getCenterY() - ent.getHeight() / 2) {
				dontMoveRect[1] = 1;
				isCollid = true;
			}
			else {
				dontMoveRect[1] = 0;
				isCollid = false;
			}

			if(bottom < ent.getCenterY() + ent.getHeight() / 2 &&
				right > ent.getCenterX() - ent.getWidth() / 2 &&
				left < ent.getCenterX() + ent.getWidth() / 2) {
				dontMoveRect[3] = 1;
				isCollid = true;
			}
			else {
				dontMoveRect[3] = 0;
				isCollid = false;
			}

			if (top > ent.getCenterY() - ent.getHeight() / 2 &&
				right > ent.getCenterX() - ent.getWidth() / 2 &&
				left < ent.getCenterX() + ent.getWidth() / 2) {
				dontMoveRect[2] = 1;
				isCollid = true;
			}
			else {
				dontMoveRect[2] = 0;
				isCollid = false;
			}

		}
		else {
			printf("Trigger ");
		}

		//std::printf("Collid");

        return true;
    }
	
	else {
		//isCollid = true;
		
	}

	/*
	if ((getCenterX() + edge.left*getScale() <= ent.getCenterX() + ent.getEdge().right*ent.getScale())) {
		if (!isTrigger) {
			setX(getX() - 8.0f);
		}
		return true;
	}*/
    return false;
}

// 각도가 틀어진 상자끼리의 충돌 여부
bool Junk2DEntity::collideRotatedBox(Junk2DEntity &ent)
{
    computeRotatedBox();                    
    ent.computeRotatedBox();               
    if (projectionsOverlap(ent) && ent.projectionsOverlap(*this))
    {
        return true;
    }
    return false;
}

// 
bool Junk2DEntity::projectionsOverlap(Junk2DEntity &ent)
{
    float projection, min01, max01, min03, max03;

    projection = graphics->Vector2Dot(&edge01, ent.getCorner(0)); 
    min01 = projection;
    max01 = projection;
    for(int c=1; c<4; c++)
    {
        projection = graphics->Vector2Dot(&edge01, ent.getCorner(c));
        if (projection < min01)
            min01 = projection;
        else if (projection > max01)
            max01 = projection;
    }
    if (min01 > edge01Max || max01 < edge01Min) 
        return false;                       

    projection = graphics->Vector2Dot(&edge03, ent.getCorner(0)); // project corner 0
    min03 = projection;
    max03 = projection;
    for(int c=1; c<4; c++)
    {
        projection = graphics->Vector2Dot(&edge03, ent.getCorner(c));
        if (projection < min03)
            min03 = projection;
        else if (projection > max03)
            max03 = projection;
    }
    if (min03 > edge03Max || max03 < edge03Min)
        return false;                       

    return true;                            
}

bool Junk2DEntity::collideRotatedBoxCircle(Junk2DEntity &ent)
{
    float min01, min03, max01, max03, center01, center03;

    computeRotatedBox();                   

    center01 = graphics->Vector2Dot(&edge01, ent.getCenter());
    min01 = center01 - ent.getRadius()*ent.getScale(); 
    max01 = center01 + ent.getRadius()*ent.getScale();
    if (min01 > edge01Max || max01 < edge01Min) 
        return false;                       
        
    center03 = graphics->Vector2Dot(&edge03, ent.getCenter());
    min03 = center03 - ent.getRadius()*ent.getScale(); 
    max03 = center03 + ent.getRadius()*ent.getScale();
    if (min03 > edge03Max || max03 < edge03Min) 
        return false;                       

    if(center01 < edge01Min && center03 < edge03Min)    
        return collideCornerCircle(corners[0], ent);
    if(center01 > edge01Max && center03 < edge03Min)    
        return collideCornerCircle(corners[1], ent);
    if(center01 > edge01Max && center03 > edge03Max)    
        return collideCornerCircle(corners[2], ent);
    if(center01 < edge01Min && center03 > edge03Max)    
        return collideCornerCircle(corners[3], ent);

    return true;
}

bool Junk2DEntity::collideCornerCircle(VECTOR2 corner, Junk2DEntity &ent)
{
    distSquared = corner - *ent.getCenter();            // corner - circle
    distSquared.x = distSquared.x * distSquared.x;      // difference squared
    distSquared.y = distSquared.y * distSquared.y;

    sumRadiiSquared = ent.getRadius()*ent.getScale();   
    sumRadiiSquared *= sumRadiiSquared;                 

    if(distSquared.x + distSquared.y <= sumRadiiSquared)
    {
        return true;
    }
    return false;
}

void Junk2DEntity::computeRotatedBox()
{
    if(rotatedBoxReady)
        return;
    float projection;

    VECTOR2 rotatedX(cos(spriteData.angle), sin(spriteData.angle));
    VECTOR2 rotatedY(-sin(spriteData.angle), cos(spriteData.angle));

    const VECTOR2 *center = getCenter();
    corners[0] = *center + rotatedX * ((float)edge.left*getScale())  +
                           rotatedY * ((float)edge.top*getScale());
    corners[1] = *center + rotatedX * ((float)edge.right*getScale()) + 
                           rotatedY * ((float)edge.top*getScale());
    corners[2] = *center + rotatedX * ((float)edge.right*getScale()) + 
                           rotatedY * ((float)edge.bottom*getScale());
    corners[3] = *center + rotatedX * ((float)edge.left*getScale())  +
                           rotatedY * ((float)edge.bottom*getScale());

    edge01 = VECTOR2(corners[1].x - corners[0].x, corners[1].y - corners[0].y);
    graphics->Vector2Normalize(&edge01);
    edge03 = VECTOR2(corners[3].x - corners[0].x, corners[3].y - corners[0].y);
    graphics->Vector2Normalize(&edge03);

    projection = graphics->Vector2Dot(&edge01, &corners[0]);
    edge01Min = projection;
    edge01Max = projection;

    projection = graphics->Vector2Dot(&edge01, &corners[1]);
    if (projection < edge01Min)
        edge01Min = projection;
    else if (projection > edge01Max)
        edge01Max = projection;

    projection = graphics->Vector2Dot(&edge03, &corners[0]);
    edge03Min = projection;
    edge03Max = projection;
    projection = graphics->Vector2Dot(&edge03, &corners[3]);
    if (projection < edge03Min)
        edge03Min = projection;
    else if (projection > edge03Max)
        edge03Max = projection;

    rotatedBoxReady = true;
}

bool Junk2DEntity::outsideRect(RECT rect)
{
    if( spriteData.x + spriteData.width*getScale() < rect.left || 
        spriteData.x > rect.right ||
        spriteData.y + spriteData.height*getScale() < rect.top || 
        spriteData.y > rect.bottom)
        return true;
    return false;
}

void Junk2DEntity::damage(int weapon)
{}

void Junk2DEntity::bounce(VECTOR2 &collisionVector, Junk2DEntity &ent)
{
	VECTOR2 Vdiff = ent.getVelocity() - velocity;
	VECTOR2 cUV = collisionVector;
	Graphics::Vector2Normalize(&cUV);
	float cUVdotVdiff = Graphics::Vector2Dot(&cUV, &Vdiff);
	float massRatio = 2.0f;
	if (getMass() != 0)
		massRatio *= (ent.getMass() / (getMass() + ent.getMass()));

	if (cUVdotVdiff > 0)
	{
		setX(getX() - cUV.x * massRatio);
		setY(getY() - cUV.y * massRatio);
	}
	else
		deltaV += ((massRatio * cUVdotVdiff) * cUV);
}

void Junk2DEntity::gravityForce()
{
    if (!active && !isGravity)
        return ;

	if (dontMoveRect[3] == 0) {
		setY(getY() + 0.98f);
	}

	//update(0.5f);
}
