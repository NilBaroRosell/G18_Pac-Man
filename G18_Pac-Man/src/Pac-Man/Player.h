#pragma once
#include "Object.h"
#include <time.h>
class Player : public Object
{
private:
	int velocity;
	int lastAnimation;
	int lastAnimationY;
	float deltaTime;
	clock_t lastTime;
	float timeDown;
	bool dying;
	void NextDyingAnimation();
	void SetNewAnimation(int _animationX, int _animationY);
public:
	int score;
	int lives;
	Vec2 actualPosition;
	Vec2 initialPosition;
	int direction;// 0 -> left, 1 -> right, 2 -> up, 3 -> down
	int lastDirection;
	Player();
	void Update(bool * _keys);
	void WallDetected();
	void SetInitialPosition(int _x, int _y);
	void AddPoints(int _points);
	void SetNewAnimation(int _animation);
	void Move();
	void Respawn();
	void Draw();
	~Player();
};

