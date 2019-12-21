#include "PowerUp.h"



PowerUp::PowerUp()
{
	points = POWERUP_DATA::POINTS;
	timeEffect = POWERUP_DATA::TIME_EFFECT;
}

void PowerUp::Update()
{

}

void PowerUp::Draw()
{
	Renderer::Instance()->PushSprite(objectId, objectSpriteRect, objectRect);
}

PowerUp::~PowerUp()
{
}
