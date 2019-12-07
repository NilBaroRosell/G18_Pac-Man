#pragma once
#include "HUD.h"
#include "SceneManager.h"

class Play : public SceneManager
{
private:
	HUD background;
	Object* map;
	void ReadConfig();
public:
	Play();
	void Update(bool * _keys, Vec2 _mousePosition);
	void Draw();
	~Play();
};

