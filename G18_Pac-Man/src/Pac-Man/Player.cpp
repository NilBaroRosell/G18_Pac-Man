#include "Player.h"



Player::Player()
{
	direction = PLAYER_INITIAL_INFO::DIRECTION;
	velocity = PLAYER_INITIAL_INFO::VELOCITY;
	score = PLAYER_INITIAL_INFO::SCORE;
	lives = PLAYER_INITIAL_INFO::LIVES;
	lastAnimation = PLAYER::X_LEFT_CLOSE_SPRITE;
	lastTime = clock();
	timeDown = 0.15f;
}

void Player::Update(bool * _keys)
{
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

	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timeDown -= deltaTime;
}

void Player::SetNewAnimation(int _animation)
{
	objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * _animation;
	objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * PLAYER::Y_SPRITE_POSITION;
	lastAnimation = _animation;
	timeDown = 0.15f;
}

void Player::SetInitialPosition(int _x, int _y)
{
	initialPosition.x = _x;
	initialPosition.y = _y;
}

void Player::WallDetected()
{
	switch (direction)
	{
	case 0:
		if (objectRect.x == SIZE * 19) objectRect.x = 0;
		else objectRect.x += velocity;
		objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * PLAYER::X_LEFT_CLOSE_SPRITE;
		objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * PLAYER::Y_SPRITE_POSITION;
		break;
	case 1:
		if (objectRect.x == 0) objectRect.x = SIZE * 19;
		else objectRect.x -= velocity;
		objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * PLAYER::X_RIGHT_CLOSE_SPRITE;
		objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * PLAYER::Y_SPRITE_POSITION;
		break;
	case 2:
		if (objectRect.y == SIZE * 19) objectRect.y = 0;
		else objectRect.y += velocity;
		objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * PLAYER::X_UP_CLOSE_SPRITE;
		objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * PLAYER::Y_SPRITE_POSITION;
		break;
	case 3:
		if (objectRect.y == 0) objectRect.y = SIZE * 19;
		else objectRect.y -= velocity;
		objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * PLAYER::X_DOWN_CLOSE_SPRITE;
		objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * PLAYER::Y_SPRITE_POSITION;
		break;
	default:
		break;
	}
} 

void Player::AddPoints(int _points)
{
	score += _points;
}

void Player::Move()
{
	switch (direction)
	{
	case 0:
		objectRect.x -= velocity;
		if (objectRect.x <= 0)
		{
			objectRect.x = SIZE * 19;
			actualPosition.x = 19;
		}
		if (lastAnimation == PLAYER::X_LEFT_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(PLAYER::X_LEFT_OPEN_SPRITE);
		}
		else if (lastAnimation == PLAYER::X_LEFT_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(PLAYER::X_LEFT_CLOSE_SPRITE);
		}
		else if (lastAnimation != PLAYER::X_LEFT_CLOSE_SPRITE && lastAnimation != PLAYER::X_LEFT_OPEN_SPRITE)
		{
			SetNewAnimation(PLAYER::X_LEFT_CLOSE_SPRITE);
		}
		break;
	case 1:
		objectRect.x += velocity;
		if (objectRect.x >= SIZE * 19)
		{
			objectRect.x = 0;
			actualPosition.x = 0;
		}
		if (lastAnimation == PLAYER::X_RIGHT_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(PLAYER::X_RIGHT_OPEN_SPRITE);
		}
		else if (lastAnimation == PLAYER::X_RIGHT_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(PLAYER::X_RIGHT_CLOSE_SPRITE);
		}
		else if (lastAnimation != PLAYER::X_RIGHT_CLOSE_SPRITE && lastAnimation != PLAYER::X_RIGHT_OPEN_SPRITE)
		{
			SetNewAnimation(PLAYER::X_RIGHT_CLOSE_SPRITE);
		}
		break;
	case 2:
		objectRect.y -= velocity;
		if (objectRect.y <= 0)
		{
			objectRect.y = SIZE * 19;
			actualPosition.y = 19;
		}
		if (lastAnimation == PLAYER::X_UP_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(PLAYER::X_UP_OPEN_SPRITE);
		}
		else if (lastAnimation == PLAYER::X_UP_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(PLAYER::X_UP_CLOSE_SPRITE);
		}
		else if (lastAnimation != PLAYER::X_UP_CLOSE_SPRITE && lastAnimation != PLAYER::X_UP_OPEN_SPRITE)
		{
			SetNewAnimation(PLAYER::X_UP_CLOSE_SPRITE);
		}
		break;
	case 3:
		objectRect.y += velocity;
		if (objectRect.y >= SIZE * 19)
		{
			objectRect.y = 0;
			actualPosition.y = 0;
		}
		if (lastAnimation == PLAYER::X_DOWN_CLOSE_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(PLAYER::X_DOWN_OPEN_SPRITE);
		}
		else if (lastAnimation == PLAYER::X_DOWN_OPEN_SPRITE && timeDown <= 0)
		{
			SetNewAnimation(PLAYER::X_DOWN_CLOSE_SPRITE);
		}
		else if (lastAnimation != PLAYER::X_DOWN_CLOSE_SPRITE && lastAnimation != PLAYER::X_DOWN_OPEN_SPRITE)
		{
			SetNewAnimation(PLAYER::X_DOWN_CLOSE_SPRITE);
		}
		break;
	default:
		break;
	}
}

void Player::Respawn()
{
	objectRect.x = initialPosition.x * SIZE;
	objectRect.y = initialPosition.y * SIZE;
	actualPosition.x = initialPosition.x;
	actualPosition.y = initialPosition.y;
	lives--;
	direction = PLAYER_INITIAL_INFO::DIRECTION;
	SetNewAnimation(PLAYER::X_LEFT_CLOSE_SPRITE);
}

void Player::Draw()
{
	Renderer::Instance()->PushSprite(objectId, objectSpriteRect, objectRect);
}

Player::~Player()
{
}
