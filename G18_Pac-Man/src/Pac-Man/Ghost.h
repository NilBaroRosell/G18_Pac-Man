#pragma once
#include "Object.h"
#include <time.h>
class Ghost : public Object
{
protected:
	Vec2 initialPosition;
	int lastAnimation;
	int lastAnimationPowerUP;
	int points;
	bool dead;
	float deltaTime;
	clock_t lastTime;
	float timeDown;
public:
	int direction; // 0 -> left, 1 -> right, 2 -> up, 3 -> down
	int lastDirection;
	Vec2 actualPosition;
	Ghost();
	virtual void Update();
	virtual void Respawn();
	virtual void SetInitialPosition(int _x, int _y);
	virtual void Draw();
	~Ghost();
};

