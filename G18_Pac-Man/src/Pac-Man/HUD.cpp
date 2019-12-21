#include "HUD.h"

HUD::HUD()
{
	hudBackground.objectId = PACMAN_SPRITESHEET::ID;
	hudBackground.objectRect = Rect{ SCREEN_HEIGHT, INITIAL_Y, HUD_WIDTH, SCREEN_HEIGHT };
	hudBackground.objectSpriteRect = Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * HUD_INFO::X_BACKGROUND, (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * HUD_INFO::Y_BACKGROUND, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE };

	hudScoreID = new std::string[4];
	hudScoreRect = new Rect[4];
	for (int i = 0; i < 4; i++)
	{
		hudScoreID[i] = SCORE_0::ID;
		hudScoreRect[i].x = HUD_INFO::SCORE_INITIAL_X + i * HUD_INFO::SCORE_W;
		hudScoreRect[i].y = HUD_INFO::SCORE_INITIAL_Y;
		hudScoreRect[i].w = HUD_INFO::SCORE_W;
		hudScoreRect[i].h = HUD_INFO::SCORE_H;
	}

	hudCherry.objectId = PACMAN_SPRITESHEET::ID;
	hudCherry.objectRect = Rect{ HUD_INFO::INITIAL_CHERRY_X, HUD_INFO::INITIAL_CHERRY_Y, HUD_INFO::CHERRY_SIZE, HUD_INFO::CHERRY_SIZE };
	hudCherry.objectSpriteRect = Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * HUD_INFO::X_CHERRY, (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * HUD_INFO::Y_CHERRY, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE };

	hudStrawberry.objectId = PACMAN_SPRITESHEET::ID;
	hudStrawberry.objectRect = Rect{ HUD_INFO::INITIAL_STRAWBERRY_X, HUD_INFO::INITIAL_STRAWBERRY_Y, HUD_INFO::STRAWBERRY_SIZE, HUD_INFO::STRAWBERRY_SIZE };
	hudStrawberry.objectSpriteRect = Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * HUD_INFO::X_STRAWBERRY, (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * HUD_INFO::Y_STRAWBERRY, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE };

	hudOrange.objectId = PACMAN_SPRITESHEET::ID;
	hudOrange.objectRect = Rect{ HUD_INFO::INITIAL_ORANGE_X, HUD_INFO::INITIAL_ORANGE_Y, HUD_INFO::ORANGE_SIZE, HUD_INFO::ORANGE_SIZE };
	hudOrange.objectSpriteRect = Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * HUD_INFO::X_ORANGE, (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * HUD_INFO::Y_ORANGE, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE };

	hudLives = new Object[PLAYER_INITIAL_INFO::LIVES];
	for (int i = 0; i < PLAYER_INITIAL_INFO::LIVES; i++)
	{
		hudLives[i].objectId = PACMAN_SPRITESHEET::ID;
		hudLives[i].objectRect = Rect{ HUD_INFO::INITIAL_LIVE_X + i * HUD_INFO::LIVE_SIZE, HUD_INFO::INITIAL_LIVE_Y, HUD_INFO::LIVE_SIZE, HUD_INFO::LIVE_SIZE };
		hudLives[i].objectSpriteRect = Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * HUD_INFO::X_LIVE, (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * HUD_INFO::Y_LIVE, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE };
	}

	hudSpaceStartID1 = PRESS_SPACE1::ID;
	hudSpaceStartRect1 = Rect{ PRESS_SPACE1::X, PRESS_SPACE1::Y, PRESS_SPACE1::W, PRESS_SPACE1::H };
	hudSpaceStartID2 = PRESS_SPACE2::ID;
	hudSpaceStartRect2 = Rect{ PRESS_SPACE2::X, PRESS_SPACE2::Y, PRESS_SPACE2::W, PRESS_SPACE2::H };
	hudSpacePauseID1 = NULL_TEXT::ID;
	hudSpacePauseRect1 = Rect{ STOP_PRESS_SPACE1::X, STOP_PRESS_SPACE1::Y, STOP_PRESS_SPACE1::W, STOP_PRESS_SPACE1::H };
	hudSpacePauseID2 = NULL_TEXT::ID;
	hudSpacePauseRect2 = Rect{ STOP_PRESS_SPACE2::X, STOP_PRESS_SPACE2::Y, STOP_PRESS_SPACE2::W, STOP_PRESS_SPACE2::H };
	hudSpacePauseID3 = NULL_TEXT::ID;
	hudSpacePauseRect3 = Rect{ STOP_PRESS_SPACE3::X, STOP_PRESS_SPACE3::Y, STOP_PRESS_SPACE3::W, STOP_PRESS_SPACE3::H };
	hudSound = Button{ SOUND_PAUSE::ID, SOUND_PAUSE::ID,  SOUND_PAUSE::X, SOUND_PAUSE::Y, SOUND_PAUSE::W, SOUND_PAUSE::H };
	hudSound.buttonId = NULL_TEXT::ID;
	hudTransparent.objectId = PACMAN_SPRITESHEET::ID;
	hudTransparent.objectRect = Rect{ INITIAL_X, INITIAL_Y, SCREEN_WIDTH, SCREEN_HEIGHT };;
	hudTransparent.objectSpriteRect = Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * HUD_INFO::X_TRANSPARENT, (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * HUD_INFO::Y_TRANSPARENT, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE };
}

void HUD::Update()
{
}

void HUD::DisableStart()
{
	hudSpaceStartID1 = NULL_TEXT::ID;
	hudSpaceStartID2 = NULL_TEXT::ID;
	hudTransparent.objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * HUD_INFO::X_NULL;
	hudTransparent.objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * HUD_INFO::Y_NULL;
}

void HUD::EnablePause()
{
	hudSpacePauseID1 = STOP_PRESS_SPACE1::ID;
	hudSpacePauseID2 = STOP_PRESS_SPACE2::ID;
	hudSpacePauseID3 = STOP_PRESS_SPACE3::ID;
	hudSound.buttonId = SOUND_PAUSE::ID;
	hudTransparent.objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * HUD_INFO::X_TRANSPARENT;
	hudTransparent.objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * HUD_INFO::Y_TRANSPARENT;
}

void HUD::DisablePause()
{
	hudSpacePauseID1 = NULL_TEXT::ID;
	hudSpacePauseID2 = NULL_TEXT::ID;
	hudSpacePauseID3 = NULL_TEXT::ID;
	hudSound.buttonId = NULL_TEXT::ID;
	hudTransparent.objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * HUD_INFO::X_NULL;
	hudTransparent.objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * HUD_INFO::Y_NULL;
}

void HUD::UpdateScoreInfo(int _playerScore)
{
	int aux = 0;
	for (int i = 3; i >= 0; i--)
	{
		aux = _playerScore % 10;
		switch (aux)
		{
		case 0:
			hudScoreID[i] = SCORE_0::ID;
			break;
		case 1:
			hudScoreID[i] = SCORE_1::ID;
			break;
		case 2:
			hudScoreID[i] = SCORE_2::ID;
			break;
		case 3:
			hudScoreID[i] = SCORE_3::ID;
			break;
		case 4:
			hudScoreID[i] = SCORE_4::ID;
			break;
		case 5:
			hudScoreID[i] = SCORE_5::ID;
			break;
		case 6:
			hudScoreID[i] = SCORE_6::ID;
			break;
		case 7:
			hudScoreID[i] = SCORE_7::ID;
			break;
		case 8:
			hudScoreID[i] = SCORE_8::ID;
			break;
		case 9:
			hudScoreID[i] = SCORE_9::ID;
			break;
		default:
			break;
		}
		_playerScore /= 10;
	}
}

void HUD::Draw(int _lives)
{
	Renderer::Instance()->PushSprite(hudBackground.objectId, hudBackground.objectSpriteRect, hudBackground.objectRect);
	for (int i = 0; i < 4; i++)
	{
		Renderer::Instance()->PushImage(hudScoreID[i], hudScoreRect[i]);
	}
	Renderer::Instance()->PushSprite(hudCherry.objectId, hudCherry.objectSpriteRect, hudCherry.objectRect);
	Renderer::Instance()->PushSprite(hudStrawberry.objectId, hudStrawberry.objectSpriteRect, hudStrawberry.objectRect);
	Renderer::Instance()->PushSprite(hudOrange.objectId, hudOrange.objectSpriteRect, hudOrange.objectRect);
	for (int i = 0; i < _lives; i++)
	{
		Renderer::Instance()->PushSprite(hudLives[i].objectId, hudLives[i].objectSpriteRect, hudLives[i].objectRect);
	}
	Renderer::Instance()->PushSprite(hudTransparent.objectId, hudTransparent.objectSpriteRect, hudTransparent.objectRect);
	Renderer::Instance()->PushImage(hudSpaceStartID1, hudSpaceStartRect1);
	Renderer::Instance()->PushImage(hudSpaceStartID2, hudSpaceStartRect2);
	Renderer::Instance()->PushImage(hudSpacePauseID1, hudSpacePauseRect1);
	Renderer::Instance()->PushImage(hudSpacePauseID2, hudSpacePauseRect2);
	Renderer::Instance()->PushImage(hudSpacePauseID3, hudSpacePauseRect3);
	Renderer::Instance()->PushImage(hudSound.buttonId, hudSound.buttonRect);
}

HUD::~HUD()
{
}