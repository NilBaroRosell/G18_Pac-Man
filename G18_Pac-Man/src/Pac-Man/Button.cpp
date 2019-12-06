#include "Button.h"

Button::Button()
{
}

Button::Button(std::string _normalId, std::string _hoverId, int _x, int _y, int _w, int _h)
{
	normalId = _normalId;
	hoverId = _hoverId;
	objectId = normalId;
	objectRect.x = _x;
	objectRect.y = _y;
	objectRect.w = _w;
	objectRect.h = _h;
}

void Button::Update(Vec2 _mousePosition)
{
	if (checkHover(_mousePosition))
	{
		objectId = hoverId;
	}
	else
	{
		objectId = normalId;
	}
}

void Button::Draw()
{
	Renderer::Instance()->PushImage(objectId, objectRect);
}

bool Button::checkHover(Vec2 _mousePos)
{
	return((_mousePos.x > objectRect.x && _mousePos.x < objectRect.x + objectRect.w) && (_mousePos.y > objectRect.y && _mousePos.y < objectRect.y + objectRect.h));
}

Button::~Button()
{
}