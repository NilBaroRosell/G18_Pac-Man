#pragma once
#include "Types.h"
#include "Renderer.h"
class Object
{
public:
	std::string objectId;
	Rect objectRect;
	Rect objectSpriteRect;
	Object();
	virtual void Update();
	virtual void Draw();
	~Object();
};