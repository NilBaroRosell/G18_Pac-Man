#include "Blinky.h"



Blinky::Blinky()
{
	points = 25;
	dead = false;
	lastDirection = BLINKY_INITIAL_INFO::DIRECTION;
	lastTime = clock();
	timeDown = 0.15f;
	directions[lastDirection] = true;
}

void Blinky::Update()
{
	if (!dead)
	{
		//input control
		switch (direction)
		{
		case 0:
			if (objectRect.x % SIZE == 0) direction = RandomDirection();
			else direction = lastDirection;
			break;
		case 1:
			if (objectRect.x % SIZE == 0) direction = RandomDirection();
			else direction = lastDirection;
			break;
		case 2:
			if (objectRect.y % SIZE == 0) direction = RandomDirection();
			else direction = lastDirection;
			break;
		case 3:
			if (objectRect.y % SIZE == 0) direction = RandomDirection();
			else direction = lastDirection;
			break;
		default:
			break;
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
			direction = BLINKY_INITIAL_INFO::DIRECTION;
			dead = false;
		}
	}
}

int Blinky::RandomDirection()
{
	int finalDirection = rand() % 4;
	if (!directions[finalDirection]) finalDirection = RandomDirection();
	return finalDirection;
}

void Blinky::Move(int _velocity)
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

void Blinky::Animate()
{
	switch (direction)
	{
	case 0:
		if (lastAnimation == BLINKY::X_LEFT_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(BLINKY::X_LEFT_OPEN_SPRITE);
		}
		else if (lastAnimation == BLINKY::X_LEFT_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(BLINKY::X_LEFT_CLOSE_SPRITE);
		}
		else if (lastAnimation != BLINKY::X_LEFT_CLOSE_SPRITE && lastAnimation != BLINKY::X_LEFT_OPEN_SPRITE)
		{
			SetNewAnimation(BLINKY::X_LEFT_CLOSE_SPRITE);
		}
		break;
	case 1:
		if (lastAnimation == BLINKY::X_RIGHT_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(BLINKY::X_RIGHT_OPEN_SPRITE);
		}
		else if (lastAnimation == BLINKY::X_RIGHT_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(BLINKY::X_RIGHT_CLOSE_SPRITE);
		}
		else if (lastAnimation != BLINKY::X_RIGHT_CLOSE_SPRITE && lastAnimation != BLINKY::X_RIGHT_OPEN_SPRITE)
		{
			SetNewAnimation(BLINKY::X_RIGHT_CLOSE_SPRITE);
		}
		break;
	case 2:
		if (lastAnimation == BLINKY::X_UP_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(BLINKY::X_UP_OPEN_SPRITE);
		}
		else if (lastAnimation == BLINKY::X_UP_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(BLINKY::X_UP_CLOSE_SPRITE);
		}
		else if (lastAnimation != BLINKY::X_UP_CLOSE_SPRITE && lastAnimation != BLINKY::X_UP_OPEN_SPRITE)
		{
			SetNewAnimation(BLINKY::X_UP_CLOSE_SPRITE);
		}
		break;
	case 3:
		if (lastAnimation == BLINKY::X_DOWN_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(BLINKY::X_DOWN_OPEN_SPRITE);
		}
		else if (lastAnimation == BLINKY::X_DOWN_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(BLINKY::X_DOWN_CLOSE_SPRITE);
		}
		else if (lastAnimation != BLINKY::X_DOWN_CLOSE_SPRITE && lastAnimation != BLINKY::X_DOWN_OPEN_SPRITE)
		{
			SetNewAnimation(BLINKY::X_DOWN_CLOSE_SPRITE);
		}
		break;
	default:
		break;
	}
}

void Blinky::AnimatePowerUp()
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

void Blinky::SetInitialPosition(int _x, int _y)
{
	initialPosition.x = _x;
	initialPosition.y = _y;
}

void Blinky::SetNewAnimation(int _animation)
{
	objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * _animation;
	objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * BLINKY::Y_SPRITE_POSITION;
	lastAnimation = _animation;
	timeDown = 0.15f;
}

void Blinky::SetNewAnimationPowerUp(int _animation)
{
	objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * _animation;
	objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * POWER_UP_INFO::Y_SPRITE_POSITION;
	lastAnimationPowerUP = _animation;
	timeDown = 0.15f;
}

void Blinky::Respawn()
{
	objectRect.x = initialPosition.x * SIZE;
	objectRect.y = initialPosition.y * SIZE;
	actualPosition.x = initialPosition.x;
	actualPosition.y = initialPosition.y;
	direction = -1;
	dead = true;
	timeDownRespawn = 2.0f;
	lastTimeRespawn = clock();
	SetNewAnimation(BLINKY::X_LEFT_OPEN_SPRITE);
}

void Blinky::Draw()
{
	Renderer::Instance()->PushSprite(objectId, objectSpriteRect, objectRect);
}

Blinky::~Blinky()
{
}
