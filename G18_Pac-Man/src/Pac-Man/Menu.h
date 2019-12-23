#pragma once
#include "SceneManager.h"
#include "Button.h"

class Menu : public SceneManager
{
private:
	Button playButton;
	Button soundButton;
	Button rankingButton;
	Button exitButton;
public:
	Menu();
	void Update(bool * _keys, Vec2 _mousePosition);
	PlayerRankingInfo GetPlayerRankingInfo();
	void Draw();
	~Menu();
};

