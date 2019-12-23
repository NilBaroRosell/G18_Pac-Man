#pragma once
#include "Inputs.h"
#include "Constants.h"
#include "SceneManager.h"
#include "SplashScreen.h"
#include "Menu.h"
#include "Play.h"
#include "Ranking.h"

class GameController
{
private:
	Inputs inputs;
	SceneManager * actualScene;
public:
	bool isRunning;
	GameStates gameState;
	PlayerRankingInfo newPlayerRankingInfo;
	GameController();
	void GoMenu();
	void GoPlay();
	void GoRankingAfterPlay();
	void GoRankingAfterMenu();
	void Run();
	void Draw();
	~GameController();
};