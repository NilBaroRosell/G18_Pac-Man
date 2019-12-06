#include "Menu.h"

Menu::Menu()
{
	playButton = Button(PLAY_BUTTON_ID, PLAY_BUTTON_HOVER_ID, PLAY_BUTTON_X, PLAY_BUTTON_Y, PLAY_BUTTON_W, PLAY_BUTTON_H);
	soundButton = Button(SOUND_BUTTON_ID, SOUND_BUTTON_HOVER_ID, SOUND_BUTTON_X, SOUND_BUTTON_Y, SOUND_BUTTON_W, SOUND_BUTTON_H);
	rankingButton = Button(RANKING_BUTTON_ID, RANKING_BUTTON_HOVER_ID, RANKING_BUTTON_X, RANKING_BUTTON_Y, RANKING_BUTTON_W, RANKING_BUTTON_H);
	exitButton = Button(EXIT_BUTTON_ID, EXIT_BUTTON_HOVER_ID, EXIT_BUTTON_X, EXIT_BUTTON_Y, EXIT_BUTTON_W, EXIT_BUTTON_H);
	state = SceneStates::WAITING_MENU;
}

void Menu::Update(bool * _keys, Vec2 _mousePosition)
{
	switch (state)
	{
		case WAITING_MENU:
			playButton.Update(_mousePosition);
			soundButton.Update(_mousePosition);
			rankingButton.Update(_mousePosition);
			exitButton.Update(_mousePosition);
			break;
		case PLAY_MENU:
			break;
		case RANKING_MENU:
			break;
		case EXIT_MENU:
			break;
		default:
			break;
	}
}

void Menu::Draw()
{
	Renderer::Instance()->SetRendreDrawColor(0, 0, 0);
	Renderer::Instance()->Clear();
	playButton.Draw();
	soundButton.Draw();
	rankingButton.Draw();
	exitButton.Draw();
	Renderer::Instance()->Render();
}


Menu::~Menu()
{
}
