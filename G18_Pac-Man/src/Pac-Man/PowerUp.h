#pragma once
#include "Object.h"
class PowerUp : public Object
{
public:
	int points;
	int timeEffect;
	PowerUp();
	void Update();
	void Draw();
	~PowerUp();
};

