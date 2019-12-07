#include "Renderer.h"

Renderer::Renderer()
{
	// --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	m_window = SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	//Initialize PNG loading
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_imageinit";

	// ---- TTF ----
	if (TTF_Init() != 0) throw"No es pot inicialitzar SDL_ttf";

	LoadTexture(SPLASH_IMAGE_ID, SPLASH_BACKGROUND_PATH);

	Font menuFont{ MENU_FONT::ID, MENU_FONT::PATH, MENU_FONT::SIZE };
	LoadFont(menuFont);

	Font playFont{ PLAY_FONT::ID, PLAY_FONT::PATH, PLAY_FONT::SIZE };
	LoadFont(playFont);

	Text playButton{ PLAY_BUTTON::ID, PLAY_BUTTON::TEXT, PLAY_BUTTON::COLOR, PLAY_BUTTON::W, PLAY_BUTTON::H };
	LoadTextureText(menuFont.id, playButton);
	Text playButtonHover{ PLAY_BUTTON::HOVER_ID, PLAY_BUTTON::HOVER_TEXT, PLAY_BUTTON::COLOR, PLAY_BUTTON::W, PLAY_BUTTON::H };
	LoadTextureText(menuFont.id, playButtonHover);

	Text soundButton{ SOUND_BUTTON::ID, SOUND_BUTTON::TEXT, SOUND_BUTTON::COLOR, SOUND_BUTTON::W, SOUND_BUTTON::H };
	LoadTextureText(menuFont.id, soundButton);
	Text soundButtonHover{ SOUND_BUTTON::HOVER_ID, SOUND_BUTTON::HOVER_TEXT, SOUND_BUTTON::COLOR, SOUND_BUTTON::W, SOUND_BUTTON::H };
	LoadTextureText(menuFont.id, soundButtonHover);

	Text rankingButton{ RANKING_BUTTON::ID, RANKING_BUTTON::TEXT, RANKING_BUTTON::COLOR, RANKING_BUTTON::W, RANKING_BUTTON::H };
	LoadTextureText(menuFont.id, rankingButton);
	Text rankingButtonHover{ RANKING_BUTTON::HOVER_ID, RANKING_BUTTON::HOVER_TEXT, RANKING_BUTTON::COLOR, RANKING_BUTTON::W, RANKING_BUTTON::H };
	LoadTextureText(menuFont.id, rankingButtonHover);

	Text exitButton{ EXIT_BUTTON::ID, EXIT_BUTTON::TEXT, EXIT_BUTTON::COLOR, EXIT_BUTTON::W, EXIT_BUTTON::H };
	LoadTextureText(menuFont.id, exitButton);
	Text exitButtonHover{ EXIT_BUTTON::HOVER_ID, EXIT_BUTTON::HOVER_TEXT, EXIT_BUTTON::COLOR, EXIT_BUTTON::W, EXIT_BUTTON::H };
	LoadTextureText(menuFont.id, exitButtonHover);

	Text spritesheet{ PACMAN_SPRITESHEET::ID, PACMAN_SPRITESHEET::TEXT, PACMAN_SPRITESHEET::COLOR, PACMAN_SPRITESHEET::W, PACMAN_SPRITESHEET::H };
	LoadTexture(spritesheet.id, PACMAN_SPRITESHEET::PATH);
};


Renderer::~Renderer()
{
	for (auto &t : m_textureData) SDL_DestroyTexture(t.second), t.second = nullptr;
	for (auto &f : m_fontData) TTF_CloseFont(f.second), f.second = nullptr;
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

};

void Renderer::Clear() { SDL_RenderClear(m_renderer); };

void Renderer::Render() { SDL_RenderPresent(m_renderer); };

void Renderer::LoadFont(Font font) {
	TTF_Font *ttfFont{ TTF_OpenFont(font.path.c_str(), font.size) };
	if (ttfFont == nullptr) throw"No espot inicialitzar TTF_Font";
	m_fontData[font.id] = ttfFont;
};

void Renderer::LoadTexture(const std::string &id, const std::string &path) {
	SDL_Texture *texture{ IMG_LoadTexture(m_renderer, path.c_str()) };
	if (texture == nullptr) throw "No s'han pogut crear les textures";
	m_textureData[id] = texture;
};

void Renderer::LoadTextureText(const std::string &fontId, Text text) {
	SDL_Surface	*tmpSurf = TTF_RenderText_Blended(m_fontData[fontId], text.text.c_str(), SDL_Color{ text.color.r, text.color.g, text.color.b,text.color.a });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_Texture *texture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	m_textureData[text.id] = texture;
	
};

Vec2 Renderer::GetTextureSize(const std::string &id) {
	int w; int h;
	SDL_QueryTexture(m_textureData[id], NULL, NULL,&w, &h);
	return {w, h};
};

void Renderer::PushImage(const std::string &id, const Rect &rect) {
	SDL_Rect newRect;
	newRect.x = rect.x;
	newRect.y = rect.y;
	newRect.w = rect.w;
	newRect.h = rect.h;
	SDL_RenderCopy(m_renderer, m_textureData[id], nullptr, &newRect);
};

void Renderer::PushSprite(const std::string &id, const Rect &rectSprite,const Rect &rectPos) {
	SDL_Rect newSprite;
	newSprite.x = rectSprite.x;
	newSprite.y = rectSprite.y;
	newSprite.w = rectSprite.w;
	newSprite.h = rectSprite.h;
	SDL_Rect newPos;
	newPos.x = rectPos.x;
	newPos.y = rectPos.y;
	newPos.w = rectPos.w;
	newPos.h = rectPos.h;
	SDL_RenderCopy(m_renderer, m_textureData[id], &newSprite, &newPos);
}

void Renderer::PushRotatedSprite(const std::string & id, const Rect & rectSprite, const Rect & rectPos, float angle){
	SDL_Point center = { rectPos.w / 2, rectPos.h / 2 };
	SDL_Rect newSprite;
	newSprite.x = rectSprite.x;
	newSprite.y = rectSprite.y;
	newSprite.w = rectSprite.w;
	newSprite.h = rectSprite.h;
	SDL_Rect newPos;
	newPos.x = rectPos.x;
	newPos.y = rectPos.y;
	newPos.w = rectPos.w;
	newPos.h = rectPos.h;
	SDL_RenderCopyEx(m_renderer, m_textureData[id], &newSprite, &newPos, angle, &center, SDL_FLIP_NONE);
}

void Renderer::SetRendreDrawColor(int r, int g, int b)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
}




Renderer* Renderer::renderer = nullptr;
