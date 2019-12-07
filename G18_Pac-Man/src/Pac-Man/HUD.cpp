#include "HUD.h"

HUD::HUD()
{
	hudBackground.objectId = PACMAN_SPRITESHEET::ID;
	hudBackground.objectRect.x = SCREEN_HEIGHT;
	hudBackground.objectRect.y = INITIAL_Y;
	hudBackground.objectRect.w = HUD_WIDTH;
	hudBackground.objectRect.h = SCREEN_HEIGHT;
	hudBackground.objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x/8)*7;
	hudBackground.objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * 6;
	hudBackground.objectSpriteRect.w = 128;
	hudBackground.objectSpriteRect.h = 128;
}

void HUD::Update()
{

}

void HUD::Draw()
{
	Renderer::Instance()->PushSprite(hudBackground.objectId, hudBackground.objectSpriteRect, hudBackground.objectRect);
}

HUD::~HUD()
{
}
