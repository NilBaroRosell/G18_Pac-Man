#pragma once
#include "Object.h"
class Item : public Object
{
public:
	int points;
	Item();
	void Update();
	void Draw();
	~Item();
};

