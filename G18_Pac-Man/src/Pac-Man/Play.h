#pragma once
#include "SceneManager.h"

class Play : public SceneManager
{
public:
	Play();
	void Update(bool * _keys, Vec2 _mousePosition);
	void Draw();
	~Play();
};

