#include "Button.h"

Button::Button()
{
}

Button::Button(std::string _normalId, std::string _hoverId, int _x, int _y, int _w, int _h)
{
	normalId = _normalId;
	hoverId = _hoverId;
	buttonId = normalId;
	buttonRect.x = _x;
	buttonRect.y = _y;
	buttonRect.w = _w;
	buttonRect.h = _h;
}

void Button::Update(bool _mousePressed, Vec2 _mousePosition)
{
	if (checkHover(_mousePosition))
	{
		if (_mousePressed) isPressed = true;
		else isPressed = false;
		buttonId = hoverId;
	}
	else
	{
		isPressed = false;
		buttonId = normalId;
	}
}

void Button::Draw()
{
	Renderer::Instance()->PushImage(buttonId, buttonRect);
}

bool Button::checkHover(Vec2 _mousePos)
{
	return((_mousePos.x > buttonRect.x && _mousePos.x < buttonRect.x + buttonRect.w) && (_mousePos.y > buttonRect.y && _mousePos.y < buttonRect.y + buttonRect.h));
}

Button::~Button()
{
}