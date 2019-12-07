#include "Ranking.h"

Ranking::Ranking()
{
	state = SceneStates::WAITING_RANKING;
}

void Ranking::Update(bool * _keys, Vec2 _mousePosition)
{
	switch (state)
	{
		case WAITING_RANKING:
			break;
		case BACK_RANKING:
			break;
		default:
			break;
	}
}

void Ranking::Draw()
{
	Renderer::Instance()->SetRendreDrawColor(0, 255, 0);
	Renderer::Instance()->Clear();
	Renderer::Instance()->Render();
}


Ranking::~Ranking()
{
}
