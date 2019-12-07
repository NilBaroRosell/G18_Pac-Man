#pragma once

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;
const int INITIAL_X = 0;
const int INITIAL_Y = 0;
const int HUD_WIDTH = 200;
const int GAME_SPRITES_SIZE = 35;

const std::string SPLASH_IMAGE_ID = "SplashImage";
const std::string SPLASH_BACKGROUND_PATH = "../../res/img/SPLASH.png";

namespace MENU_FONT
{
	const std::string ID = "MenuFont";
	const std::string PATH = "../../res/ttf/PAC-FONT.ttf";
	const int SIZE = 30;
}

namespace PLAY_FONT
{
	const std::string ID = "PlayFont";
	const std::string PATH = "../../res/ttf/Gameplay.ttf";
	const int SIZE = 20;
}

namespace PLAY_BUTTON
{
	const std::string ID = "PlayButton";
	const std::string TEXT = "PLAY";
	const std::string HOVER_ID = "PlayButtonHover";
	const std::string HOVER_TEXT = "play";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 150;
	const int H = 50;
	const int X = 100;
	const int Y = 100;
}

namespace SOUND_BUTTON
{
	const std::string ID = "SoundButton";
	const std::string TEXT = "SOUND ON-OFF";
	const std::string HOVER_ID = "SoundButtonHover";
	const std::string HOVER_TEXT = "sound on-off";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 375;
	const int H = 50;
	const int X = 100;
	const int Y = 250;
}

namespace RANKING_BUTTON
{
	const std::string ID = "RankingButton";
	const std::string TEXT = "RANKING";
	const std::string HOVER_ID = "RankingButtonHover";
	const std::string HOVER_TEXT = "ranking";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 250;
	const int H = 50;
	const int X = 100;
	const int Y = 400;
}

namespace EXIT_BUTTON
{
	const std::string ID = "ExitButton";
	const std::string TEXT = "EXIT";
	const std::string HOVER_ID = "ExitButtonHover";
	const std::string HOVER_TEXT = "exit";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 125;
	const int H = 50;
	const int X = 100;
	const int Y = 550;
}

namespace PACMAN_SPRITESHEET
{
	const std::string ID = "PacmanSpritesheet";
	const std::string TEXT = "";
	const std::string PATH = "../../res/img/PacManSpritesheet.png";
	const Color COLOR = Color(255, 255, 255, 0);
	const int W = 1024;
	const int H = 1024;
}