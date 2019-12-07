#include "Menu.h"

Menu::Menu()
{
	playButton = Button(PLAY_BUTTON::ID, PLAY_BUTTON::HOVER_ID, PLAY_BUTTON::X, PLAY_BUTTON::Y, PLAY_BUTTON::W, PLAY_BUTTON::H);
	soundButton = Button(SOUND_BUTTON::ID, SOUND_BUTTON::HOVER_ID, SOUND_BUTTON::X, SOUND_BUTTON::Y, SOUND_BUTTON::W, SOUND_BUTTON::H);
	rankingButton = Button(RANKING_BUTTON::ID, RANKING_BUTTON::HOVER_ID, RANKING_BUTTON::X, RANKING_BUTTON::Y, RANKING_BUTTON::W, RANKING_BUTTON::H);
	exitButton = Button(EXIT_BUTTON::ID, EXIT_BUTTON::HOVER_ID, EXIT_BUTTON::X, EXIT_BUTTON::Y, EXIT_BUTTON::W, EXIT_BUTTON::H);
	state = SceneStates::WAITING_MENU;
}

void Menu::Update(bool * _keys, Vec2 _mousePosition)
{
	switch (state)
	{
		case WAITING_MENU:
			playButton.Update(_keys[(int)InputKey::K_MOUSE], _mousePosition);
			soundButton.Update(_keys[(int)InputKey::K_MOUSE], _mousePosition);
			rankingButton.Update(_keys[(int)InputKey::K_MOUSE], _mousePosition);
			exitButton.Update(_keys[(int)InputKey::K_MOUSE], _mousePosition);
			if (playButton.isPressed) state = SceneStates::PLAY_MENU;
			else if (soundButton.isPressed) std::cout << "SOUND ENABLED" << std::endl;
			else if (rankingButton.isPressed) state = SceneStates::RANKING_MENU;
			else if (exitButton.isPressed) state = SceneStates::EXIT_MENU;
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
