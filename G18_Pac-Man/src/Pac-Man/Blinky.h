#pragma once
#include "Ghost.h"
class Blinky : public Ghost
{
public:
	bool directions[4];
	Blinky();
	void Update();
	int RandomDirection();
	void Move(int _velocity);
	void Animate();
	void AnimatePowerUp();
	void SetInitialPosition(int _x, int _y);
	void SetNewAnimation(int _animation);
	void SetNewAnimationPowerUp(int _animation);
	void Respawn();
	void Draw();
	~Blinky();
};