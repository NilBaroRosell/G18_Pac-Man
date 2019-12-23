#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
	backgroundId = SPLASH_IMAGE_ID;
	backgroundRect.h = SCREEN_HEIGHT;
	backgroundRect.w = SCREEN_WIDTH;
	backgroundRect.x = INITIAL_X;
	backgroundRect.y = INITIAL_Y;
	lastTime = clock();
	timeDown = 3;
	state = SceneStates::WAITING_SPLASH;
}

void SplashScreen::Update(bool * _keys, Vec2 _mousePosition)
{
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timeDown -= deltaTime;
	switch (state)
	{
		case WAITING_SPLASH:
			if (timeDown <= 0)
			{
				state = SceneStates::MENU_SPLASH;
			}
			break;
		default:
			break;
	}
}

PlayerRankingInfo SplashScreen::GetPlayerRankingInfo()
{
	return { NULL, NULL };
}

void SplashScreen::Draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage(backgroundId, backgroundRect);
	Renderer::Instance()->Render();
}

SplashScreen::~SplashScreen()
{
}
