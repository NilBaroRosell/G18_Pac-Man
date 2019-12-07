#pragma once
#include "Types.h"
#include "Renderer.h"
class Button
{
private:
	std::string normalId;
	std::string hoverId;
public:
	bool isPressed;
	std::string buttonId;
	Rect buttonRect;
	Button();
	Button(std::string _id, std::string _hoverId, int _x, int _y, int _w, int _h);
	void Update(bool _mousePressed, Vec2 _mousePosition);
	void Draw();
	bool checkHover(Vec2 _mousePos);
	~Button();
};

