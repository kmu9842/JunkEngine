#include "..\\Headers\\entity.h"

Entity::Entity() : Junk2DSprite()
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
active = true;                  // ��ƼƼ Ȱ��ȭ
rotatedBoxReady = false;
collisionType = entityNS::BOX;
gravity = entityNS::GRAVITY;
collisionTag = "None";
isTrigger = false;
}

// �浹ü �ʱ�ȭ
void Entity::initialize(Graphics *g, const char * filename, int width, int height, int ncols)
{
	Junk2DSprite::settingTexture(g, filename, width, height, ncols);

	center.x = 0.0f;
	center.y = 0.0f;

	edge.left = spriteData.rect.left;
	edge.top = spriteData.rect.top;
	edge.right = spriteData.rect.right;
	edge.bottom = spriteData.rect.bottom;
}

// �浹ü Ȱ��ȭ
void Entity::activate()
{
	active = true;
}

// �浹ü ������Ʈ
void Entity::update(float frameTime)
{
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	Junk2DSprite::update(frameTime);
	rotatedBoxReady = false;    // ȸ�� ����
}

void Entity::ai(float frameTime, Entity &ent)
{}

// ent���� �浹 ����
bool Entity::collidesWith(Entity &ent) {
	// if either entity is not active then no collision may occcur
	if (!active || !ent.getActive())
		return false;
	if (collisionType == entityNS::CIRCLE && ent.getCollisionType() == entityNS::CIRCLE)
		return collideCircle(ent);
	if (collisionType == entityNS::BOX && ent.getCollisionType() == entityNS::BOX)
		return collideBox(ent);
	if (collisionType != entityNS::CIRCLE && ent.getCollisionType() != entityNS::CIRCLE)
		return collideRotatedBox(ent);
	if (collisionType == entityNS::CIRCLE)
	{
		bool collide = ent.collideRotatedBoxCircle(*this);
		return collide;
	}
	else
		return collideRotatedBoxCircle(ent);
	return false;
}

// ���� �浹ü������ �浹 ����
bool Entity::collideCircle(Entity &ent) {
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

// ������ �浹ü������ �浹 ����
bool Entity::collideBox(Entity &ent)
{
	// Ȱ�� ����
	if (!active || !ent.getActive())
		return false;

	if ((getCenterX() + edge.right*getScale() >= ent.getCenterX() + ent.getEdge().left*ent.getScale()) &&
		(getCenterX() + edge.left*getScale() <= ent.getCenterX() + ent.getEdge().right*ent.getScale()) &&
		(getCenterY() + edge.bottom*getScale() >= ent.getCenterY() + ent.getEdge().top*ent.getScale()) &&
		(getCenterY() + edge.top*getScale() <= ent.getCenterY() + ent.getEdge().bottom*ent.getScale()))
	{
		if (!isTrigger) {
			//printf("%f\n", getCenterX() + edge.right * getScale());
			//printf("%f\n", ent.getCenterX() + ent.edge.left * ent.getScale());

			if (getCenterX() + edge.right * getScale() >= ent.getCenterX() + ent.edge.left * ent.getScale() &&
				getCenterX() + edge.right * getScale() <= (ent.getCenterX() + ent.edge.right  * ent.getScale()) &&
				!((getCenterX() + edge.right * getScale()) - (ent.getCenterX() + ent.edge.left * ent.getScale())
					>= (getCenterY() + edge.bottom * getScale()) - (ent.getCenterY() + ent.edge.top * ent.getScale())) &&
				!((getCenterX() + edge.right * getScale()) - (ent.getCenterX() + ent.edge.left * ent.getScale())
					>= (ent.getCenterY() + ent.edge.bottom * ent.getScale() - (getCenterY() + edge.top * getScale())))) {
				setX(getX() - 1);
			}

			else if (getCenterX() + edge.left * getScale() <= ent.getCenterX() + ent.edge.right * ent.getScale() &&
				getCenterX() + edge.left * getScale() >= (ent.getCenterX() + ent.edge.left  * ent.getScale()) &&
				!(((ent.getCenterX() + ent.edge.right * ent.getScale()) - (getCenterX() + edge.left * getScale()))
					>= (getCenterY() + edge.bottom * getScale()) - (ent.getCenterY() + ent.edge.top * ent.getScale())) &&
				!(((ent.getCenterX() + ent.edge.right * ent.getScale()) - (getCenterX() + edge.left * getScale()))
					>= (ent.getCenterY() + ent.edge.bottom * ent.getScale() - (getCenterY() + edge.top * getScale())))) {
				setX(getX() + 1);
			}

			else if (getCenterY() + edge.bottom * getScale() >= ent.getCenterY() + ent.edge.top * ent.getScale() &&
				getCenterY() + edge.bottom * getScale() <= (ent.getCenterY() + ent.edge.bottom  * ent.getScale())) {
				setY(getY() - 1);
			}

			else if (getCenterY() + edge.top * getScale() <= ent.getCenterY() + ent.edge.bottom * ent.getScale() &&
				getCenterY() + edge.top * getScale() >= (ent.getCenterY() + ent.edge.top  * ent.getScale())) {
				setY(getY() + 1);
			}
			/*printf("%f %f %f %f\n", getCenterX() + edge.right, getCenterX() + edge.left, 
				getCenterY() + edge.top, getCenterY() + edge.bottom);
			printf("%f %f %f %f\n", ent.getCenterX() + ent.edge.right, ent.getCenterX() + ent.edge.left,
				ent.getCenterY() + ent.edge.top, ent.getCenterY() + ent.edge.bottom);
		*/}
        return true;
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

// ������ Ʋ���� ���ڳ����� �浹 ����
bool Entity::collideRotatedBox(Entity &ent)
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
bool Entity::projectionsOverlap(Entity &ent)
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

bool Entity::collideRotatedBoxCircle(Entity &ent)
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

bool Entity::collideCornerCircle(VECTOR2 corner, Entity &ent)
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

void Entity::computeRotatedBox()
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

bool Entity::outsideRect(RECT rect)
{
    if( spriteData.x + spriteData.width*getScale() < rect.left || 
        spriteData.x > rect.right ||
        spriteData.y + spriteData.height*getScale() < rect.top || 
        spriteData.y > rect.bottom)
        return true;
    return false;
}

void Entity::damage(int weapon)
{}

void Entity::bounce(VECTOR2 &collisionVector, Entity &ent)
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

void Entity::gravityForce(Entity *ent, float frameTime)
{
    if (!active || !ent->getActive())
        return ;

    rr = pow((ent->getCenterX() - getCenterX()),2) + 
            pow((ent->getCenterY() - getCenterY()),2);
    force = gravity * ent->getMass() * mass/rr;

    VECTOR2 gravityV(ent->getCenterX() - getCenterX(),
                        ent->getCenterY() - getCenterY());

    Graphics::Vector2Normalize(&gravityV);

    gravityV *= force * frameTime;

    velocity += gravityV;
}
