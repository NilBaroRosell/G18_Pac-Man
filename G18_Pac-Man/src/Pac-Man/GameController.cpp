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

void GameController::GoRanking()
{
	gameState = GameStates::RANKING;
	delete actualScene;
	actualScene = new Ranking();
}

void GameController::Run()
{
	inputs.UpdateInputs();

	switch (gameState)
	{
		case GameStates::SPLASH_SCREEN:
			if (actualScene->state == SceneStates::MENU_SPLASH)
			{
				GoMenu();
			}
			break;
		case GameStates::MENU:
			break;
		case GameStates::PLAY:
			break;
		case GameStates::RANKING:
			break;
		case GameStates::EXIT:
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