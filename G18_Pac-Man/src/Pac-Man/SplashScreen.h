#pragma once
#include "SceneManager.h"
#include <time.h>

class SplashScreen: public SceneManager
{
private:	
	std::string backgroundId;
	Rect backgroundRect;
	float deltaTime;
	clock_t lastTime;
	float timeDown;
public:
	SplashScreen();
	void Update(bool * _keys, Vec2 _mousePosition);
	PlayerRankingInfo GetPlayerRankingInfo();
	void Draw();
	~SplashScreen();
};

