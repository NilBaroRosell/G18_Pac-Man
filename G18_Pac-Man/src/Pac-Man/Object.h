#pragma once
#include "Types.h"
#include "Play.h"
class Object
{
protected:
	std::string objectId;
	Rect objectRect;
public:
	Object();
	virtual void Update();
	virtual void Draw();
	~Object();
};