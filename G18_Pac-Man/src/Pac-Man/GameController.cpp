#include "GameController.h"

GameController::GameController()
{
	isRunning = true;
	gameState = GameStates::SPLASH_SCREEN;
	actualScene = new SplashScreen();
}

void GameController::GoMenu()
{
	gameState = GameStates::MENU;
	delete actualScene;
	actualScene = new Menu();
}

void GameController::GoPlay()
{
	gameState = GameStates::PLAY;
	delete actualScene;
	actualScene = new Play();
}

void GameController::GoRankingAfterMenu()
{
	gameState = GameStates::RANKING;
	delete actualScene;
	actualScene = new Ranking();
}

void GameController::GoRankingAfterPlay()
{
	gameState = GameStates::RANKING;
	delete actualScene;
	actualScene = new Ranking(newPlayerRankingInfo);
}

void GameController::Run()
{
	inputs.UpdateInputs();

	if (inputs.GetKey(InputKey::QUIT)) gameState = GameStates::EXIT;

	switch (gameState)
	{
		case GameStates::SPLASH_SCREEN:
			if (actualScene->state == SceneStates::MENU_SPLASH)
			{
				GoMenu();
			}
			break;
		case GameStates::MENU:
			if (actualScene->state == SceneStates::PLAY_MENU)
			{
				GoPlay();
			}
			if (actualScene->state == SceneStates::RANKING_MENU)
			{
				GoRankingAfterMenu();
			}
			if (actualScene->state == SceneStates::EXIT_MENU)
			{
				gameState = GameStates::EXIT;
			}
			break;
		case GameStates::PLAY:
			if (actualScene->state == SceneStates::GAME_OVER_PLAY)
			{
				newPlayerRankingInfo = actualScene->GetPlayerRankingInfo();
				GoRankingAfterPlay();
			}
			break;
		case GameStates::RANKING:
			if (actualScene->state == SceneStates::BACK_RANKING)
			{
				GoMenu();
			}
			break;
		case GameStates::EXIT:
			isRunning = false;
			break;
		default:
			break;
	}

	actualScene->Update(inputs.GetInputs(), inputs.GetMousePosition());
	Draw();
}

void GameController::Draw()
{
	actualScene->Draw();
}

GameController::~GameController()
{
}