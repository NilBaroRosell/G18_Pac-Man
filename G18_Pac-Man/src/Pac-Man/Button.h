#pragma once
#include "Object.h"
class Button : public Object
{
	std::string normalId;
	std::string hoverId;
public:
	Button();
	Button(std::string _id, std::string _hoverId, int _x, int _y, int _w, int _h);
	void Update(Vec2 _mousePosition);
	void Draw();
	bool checkHover(Vec2 _mousePos);
	~Button();
};

