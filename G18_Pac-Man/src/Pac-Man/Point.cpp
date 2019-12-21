#include "Point.h"



Point::Point()
{
	points = POINT_DATA::POINTS;
}

void Point::Update()
{

}

void Point::Draw()
{
	Renderer::Instance()->PushSprite(objectId, objectSpriteRect, objectRect);
}

Point::~Point()
{
}
