#pragma once
#include "Types.h"
#include "Inputs.h"
#include "Constants.h"
#include "Renderer.h"

class SceneManager
{
public:
	SceneStates state;
	SceneManager();
	virtual void Update(bool * _keys, Vec2 _mousePosition) = 0;
	virtual void Draw() = 0;
	~SceneManager();
};

