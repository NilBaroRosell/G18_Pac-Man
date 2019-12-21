#pragma once
#include "Ghost.h"
class Inky : public Ghost
{
public:
	Inky();
	void Update(bool* _keys);
	void Move(int _velocity);
	void Animate();
	void AnimatePowerUp();
	void SetInitialPosition(int _x, int _y);
	void SetNewAnimation(int _animation);
	void SetNewAnimationPowerUp(int _animation);
	void Respawn();
	void Draw();
	~Inky();
};

