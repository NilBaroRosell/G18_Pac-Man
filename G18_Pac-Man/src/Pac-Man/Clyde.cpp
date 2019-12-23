#include "Clyde.h"

Clyde::Clyde()
{
	points = 10;
	dead = false;
	lastAnimationPowerUP = POWER_UP_INFO::X_GREY_2_SPRITE;
	direction = CLYDE_INITIAL_INFO::DIRECTION;
	lastTime = clock();
	timeDown = 0.15f;
}

void Clyde::Update(bool* _keys)
{
	if (!dead)
	{
		//input control
		if (_keys[(int)InputKey::K_LEFT])
		{
			direction = 1;
		}
		else if (_keys[(int)InputKey::K_RIGHT])
		{
			direction = 0;
		}
		else if (_keys[(int)InputKey::K_UP])
		{
			direction = 3;
		}
		else if (_keys[(int)InputKey::K_DOWN])
		{
			direction = 2;
		}

		//update
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
	}
	else
	{
		deltaTimeRespawn = (clock() - lastTimeRespawn);
		lastTimeRespawn = clock();
		deltaTimeRespawn /= CLOCKS_PER_SEC;
		timeDownRespawn -= deltaTimeRespawn;
		if (timeDownRespawn <= 0)
		{
			direction = CLYDE_INITIAL_INFO::DIRECTION;
			dead = false;
		}
	}
}

void Clyde::Move(int _velocity)
{
	switch (direction)
	{
	case 0:
		objectRect.x -= _velocity;
		if (objectRect.x <= 0) objectRect.x = SIZE * 19;
		break;
	case 1:
		objectRect.x += _velocity;
		if (objectRect.x >= SIZE * 19) objectRect.x = 0;
		break;
	case 2:
		objectRect.y -= _velocity;
		if (objectRect.y <= 0) objectRect.y = SIZE * 19;
		break;
	case 3:
		objectRect.y += _velocity;
		if (objectRect.y >= SIZE * 19) objectRect.y = 0;
		break;
	default:
		break;
	}
}

void Clyde::Animate()
{
	switch (direction)
	{
	case 0:
		if (lastAnimation == CLYDE::X_LEFT_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(CLYDE::X_LEFT_OPEN_SPRITE);
		}
		else if (lastAnimation == CLYDE::X_LEFT_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(CLYDE::X_LEFT_CLOSE_SPRITE);
		}
		else if (lastAnimation != CLYDE::X_LEFT_CLOSE_SPRITE && lastAnimation != CLYDE::X_LEFT_OPEN_SPRITE)
		{
			SetNewAnimation(CLYDE::X_LEFT_CLOSE_SPRITE);
		}
		break;
	case 1:
		if (lastAnimation == CLYDE::X_RIGHT_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(CLYDE::X_RIGHT_OPEN_SPRITE);
		}
		else if (lastAnimation == CLYDE::X_RIGHT_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(CLYDE::X_RIGHT_CLOSE_SPRITE);
		}
		else if (lastAnimation != CLYDE::X_RIGHT_CLOSE_SPRITE && lastAnimation != CLYDE::X_RIGHT_OPEN_SPRITE)
		{
			SetNewAnimation(CLYDE::X_RIGHT_CLOSE_SPRITE);
		}
		break;
	case 2:
		if (lastAnimation == CLYDE::X_UP_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(CLYDE::X_UP_OPEN_SPRITE);
		}
		else if (lastAnimation == CLYDE::X_UP_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(CLYDE::X_UP_CLOSE_SPRITE);
		}
		else if (lastAnimation != CLYDE::X_UP_CLOSE_SPRITE && lastAnimation != CLYDE::X_UP_OPEN_SPRITE)
		{
			SetNewAnimation(CLYDE::X_UP_CLOSE_SPRITE);
		}
		break;
	case 3:
		if (lastAnimation == CLYDE::X_DOWN_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(CLYDE::X_DOWN_OPEN_SPRITE);
		}
		else if (lastAnimation == CLYDE::X_DOWN_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(CLYDE::X_DOWN_CLOSE_SPRITE);
		}
		else if (lastAnimation != CLYDE::X_DOWN_CLOSE_SPRITE && lastAnimation != CLYDE::X_DOWN_OPEN_SPRITE)
		{
			SetNewAnimation(CLYDE::X_DOWN_CLOSE_SPRITE);
		}
		break;
	default:
		break;
	}
}

void Clyde::AnimatePowerUp()
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

void Clyde::SetInitialPosition(int _x, int _y)
{
	initialPosition.x = _x;
	initialPosition.y = _y;
}

void Clyde::SetNewAnimation(int _animation)
{
	objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * _animation;
	objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * CLYDE::Y_SPRITE_POSITION;
	lastAnimation = _animation;
	timeDown = 0.15f;
}

void Clyde::SetNewAnimationPowerUp(int _animation)
{
	objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * _animation;
	objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * POWER_UP_INFO::Y_SPRITE_POSITION;
	lastAnimationPowerUP = _animation;
	timeDown = 0.15f;
}

void Clyde::Respawn()
{
	objectRect.x = initialPosition.x * SIZE;
	objectRect.y = initialPosition.y * SIZE;
	actualPosition.x = initialPosition.x;
	actualPosition.y = initialPosition.y;
	direction = -1;
	dead = true;
	timeDownRespawn = 2.0f;
	lastTimeRespawn = clock();
	SetNewAnimation(CLYDE::X_LEFT_OPEN_SPRITE);
}

void Clyde::Draw()
{
	Renderer::Instance()->PushSprite(objectId, objectSpriteRect, objectRect);
}

Clyde::~Clyde()
{
}
