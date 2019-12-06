#pragma once
#include "SceneManager.h"

class Ranking : public SceneManager
{
public:
	Ranking();
	void Update(bool * _keys, Vec2 _mousePosition);
	void Draw();
	~Ranking();
};

