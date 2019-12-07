#pragma once
#include "Object.h"
class HUD
{
private:
	Object hudBackground;
	Object hudScore;
	Object hudCherry;
	Object hudCherryScore;
	Object hudStrawberry;
	Object hudStrawberryScore;
	Object hudOrange;
	Object hudOrangeScore;
	Object live1;
	Object live2;
	Object live3;
public:
	HUD();
	void Update();
	void Draw();
	~HUD();
};

