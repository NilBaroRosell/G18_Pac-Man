#include "Inky.h"



Inky::Inky()
{
	points = 10;
	dead = false;
	lastAnimationPowerUP = POWER_UP_INFO::X_GREY_2_SPRITE;
	lastDirection = INKY_INITIAL_INFO::DIRECTION;
	lastTime = clock();
	timeDown = 0.15f;
}

void Inky::Update(bool* _keys)
{
	if (!dead)
	{
		//input control
		if (_keys[(int)InputKey::K_LEFT])
		{
			direction = 0;
		}
		else if (_keys[(int)InputKey::K_RIGHT])
		{
			direction = 1;
		}
		else if (_keys[(int)InputKey::K_UP])
		{
			direction = 2;
		}
		else if (_keys[(int)InputKey::K_DOWN])
		{
			direction = 3;
		}
		else
		{
			direction = lastDirection;
		}

		//update
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
	}
}

void Inky::Move(int _velocity)
{
	switch (direction)
	{
	case 0:
		objectRect.x -= _velocity;
		if (objectRect.x <= 0)
		{
			objectRect.x = SIZE * 19;
			actualPosition.x = 19;
		}
		break;
	case 1:
		objectRect.x += _velocity;
		if (objectRect.x >= SIZE * 19)
		{
			objectRect.x = 0;
			actualPosition.x = 0;
		}
		break;
	case 2:
		objectRect.y -= _velocity;
		if (objectRect.y <= 0)
		{
			objectRect.y = SIZE * 19;
			actualPosition.y = 19;
		}
		break;
	case 3:
		objectRect.y += _velocity;
		if (objectRect.y >= SIZE * 19)
		{
			objectRect.y = 0;
			actualPosition.y = 0;
		}

		break;
	default:
		break;
	}
}

void Inky::Animate()
{
	switch (direction)
	{
	case 0:
		if (lastAnimation == INKY::X_LEFT_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(INKY::X_LEFT_OPEN_SPRITE);
		}
		else if (lastAnimation == INKY::X_LEFT_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(INKY::X_LEFT_CLOSE_SPRITE);
		}
		else if (lastAnimation != INKY::X_LEFT_CLOSE_SPRITE && lastAnimation != INKY::X_LEFT_OPEN_SPRITE)
		{
			SetNewAnimation(INKY::X_LEFT_CLOSE_SPRITE);
		}
		break;
	case 1:
		if (lastAnimation == INKY::X_RIGHT_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(INKY::X_RIGHT_OPEN_SPRITE);
		}
		else if (lastAnimation == INKY::X_RIGHT_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(INKY::X_RIGHT_CLOSE_SPRITE);
		}
		else if (lastAnimation != INKY::X_RIGHT_CLOSE_SPRITE && lastAnimation != INKY::X_RIGHT_OPEN_SPRITE)
		{
			SetNewAnimation(INKY::X_RIGHT_CLOSE_SPRITE);
		}
		break;
	case 2:
		if (lastAnimation == INKY::X_UP_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(INKY::X_UP_OPEN_SPRITE);
		}
		else if (lastAnimation == INKY::X_UP_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(INKY::X_UP_CLOSE_SPRITE);
		}
		else if (lastAnimation != INKY::X_UP_CLOSE_SPRITE && lastAnimation != INKY::X_UP_OPEN_SPRITE)
		{
			SetNewAnimation(INKY::X_UP_CLOSE_SPRITE);
		}
		break;
	case 3:
		if (lastAnimation == INKY::X_DOWN_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(INKY::X_DOWN_OPEN_SPRITE);
		}
		else if (lastAnimation == INKY::X_DOWN_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(INKY::X_DOWN_CLOSE_SPRITE);
		}
		else if (lastAnimation != INKY::X_DOWN_CLOSE_SPRITE && lastAnimation != INKY::X_DOWN_OPEN_SPRITE)
		{
			SetNewAnimation(INKY::X_DOWN_CLOSE_SPRITE);
		}
		break;
	default:
		break;
	}
}

void Inky::AnimatePowerUp()
{
	if (lastAnimationPowerUP == POWER_UP_INFO::X_GREY_2_SPRITE && timeDown <= 0)
	{
		SetNewAnimationPowerUp(POWER_UP_INFO::X_BLUE_1_SPRITE);
	}
	else if (lastAnimationPowerUP == POWER_UP_INFO::X_BLUE_1_SPRITE && timeDown <= 0)
	{
		SetNewAnimationPowerUp(POWER_UP_INFO::X_BLUE_2_SPRITE);
	}
	else if (lastAnimationPowerUP == POWER_UP_INFO::X_BLUE_2_SPRITE && timeDown <= 0)
	{
		SetNewAnimationPowerUp(POWER_UP_INFO::X_GREY_1_SPRITE);
	}
	else if (lastAnimationPowerUP == POWER_UP_INFO::X_GREY_1_SPRITE && timeDown <= 0)
	{
		SetNewAnimationPowerUp(POWER_UP_INFO::X_GREY_2_SPRITE);
	}
}

void Inky::SetInitialPosition(int _x, int _y)
{
	initialPosition.x = _x;
	initialPosition.y = _y;
}

void Inky::SetNewAnimation(int _animation)
{
	objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * _animation;
	objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * INKY::Y_SPRITE_POSITION;
	lastAnimation = _animation;
	timeDown = 0.15f;
}

void Inky::SetNewAnimationPowerUp(int _animation)
{
	objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * _animation;
	objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * POWER_UP_INFO::Y_SPRITE_POSITION;
	lastAnimationPowerUP = _animation;
	timeDown = 0.15f;
}

void Inky::Respawn()
{
	objectRect.x = initialPosition.x * SIZE;
	objectRect.y = initialPosition.y * SIZE;
	actualPosition.x = initialPosition.x;
	actualPosition.y = initialPosition.y;
	direction = INKY_INITIAL_INFO::DIRECTION;
}

void Inky::Draw()
{
	Renderer::Instance()->PushSprite(objectId, objectSpriteRect, objectRect);
}

Inky::~Inky()
{
}
