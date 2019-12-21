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
	const int W = 275;
	const int H = 100;
	const int X = 335;
	const int Y = 125;
}

namespace RANKING_BUTTON
{
	const std::string ID = "RankingButton";
	const std::string TEXT = "RANKING";
	const std::string HOVER_ID = "RankingButtonHover";
	const std::string HOVER_TEXT = "ranking";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 255;
	const int H = 50;
	const int X = 335;
	const int Y = 275;
}

namespace SOUND_BUTTON
{
	const std::string ID = "SoundButton";
	const std::string TEXT = "SOUND ON";
	const std::string HOVER_ID = "SoundButtonHover";
	const std::string HOVER_TEXT = "sound on";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 350;
	const int H = 50;
	const int X = 285;
	const int Y = 375;
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
	const int X = 395;
	const int Y = 475;
}

namespace PACMAN_SPRITESHEET
{
	const std::string ID = "PacmanSpritesheet";
	const std::string TEXT = "";
	const std::string PATH = "../../res/img/PacManSpritesheet.png";
	const Color COLOR = Color(255, 255, 255, 0);
	const int W = 1024;
	const int H = 1024;
	const int SPRITES_SIZE = 128;
}

const int SIZE = GAME_SPRITES_SIZE;

namespace PLAYER 
{
	const int X_UP_OPEN_SPRITE = 0;
	const int X_UP_CLOSE_SPRITE = 1;
	const int X_DOWN_OPEN_SPRITE = 2;
	const int X_DOWN_CLOSE_SPRITE = 3;
	const int X_RIGHT_OPEN_SPRITE = 4;
	const int X_RIGHT_CLOSE_SPRITE = 5;
	const int X_LEFT_OPEN_SPRITE = 6;
	const int X_LEFT_CLOSE_SPRITE = 7;
	const int Y_SPRITE_POSITION = 0;
}

namespace BLINKY
{
	const int X_UP_OPEN_SPRITE = 0;
	const int X_UP_CLOSE_SPRITE = 1;
	const int X_DOWN_OPEN_SPRITE = 2;
	const int X_DOWN_CLOSE_SPRITE = 3;
	const int X_RIGHT_OPEN_SPRITE = 4;
	const int X_RIGHT_CLOSE_SPRITE = 5;
	const int X_LEFT_OPEN_SPRITE = 6;
	const int X_LEFT_CLOSE_SPRITE = 7;
	const int Y_SPRITE_POSITION = 1;
}

namespace INKY
{
	const int X_UP_OPEN_SPRITE = 0;
	const int X_UP_CLOSE_SPRITE = 1;
	const int X_DOWN_OPEN_SPRITE = 2;
	const int X_DOWN_CLOSE_SPRITE = 3;
	const int X_RIGHT_OPEN_SPRITE = 4;
	const int X_RIGHT_CLOSE_SPRITE = 5;
	const int X_LEFT_OPEN_SPRITE = 6;
	const int X_LEFT_CLOSE_SPRITE = 7;
	const int Y_SPRITE_POSITION = 2;
}

namespace CLYDE
{
	const int X_UP_OPEN_SPRITE = 0;
	const int X_UP_CLOSE_SPRITE = 1;
	const int X_DOWN_OPEN_SPRITE = 2;
	const int X_DOWN_CLOSE_SPRITE = 3;
	const int X_RIGHT_OPEN_SPRITE = 4;
	const int X_RIGHT_CLOSE_SPRITE = 5;
	const int X_LEFT_OPEN_SPRITE = 6;
	const int X_LEFT_CLOSE_SPRITE = 7;
	const int Y_SPRITE_POSITION = 3;
}

namespace POWERUP
{
	const int X_SPRITE_POSITION = 6;
	const int Y_SPRITE_POSITION = 6;
}

namespace WALL
{
	const int X_SPRITE_POSITION = 4;
	const int Y_SPRITE_POSITION = 6;
}

namespace POINT
{
	const int X_SPRITE_POSITION = 5;
	const int Y_SPRITE_POSITION = 6;
}

namespace PLAYER_INITIAL_INFO
{
	const int DIRECTION = 0;
	const int VELOCITY = 2;
	const int SCORE = 0;
	const int LIVES = 3;
}

namespace POWERUP_DATA
{
	const int POINTS = 20;
	const int TIME_EFFECT = 10;
}

namespace POINT_DATA
{
	const int POINTS = 1;
}

namespace BLINKY_INITIAL_INFO
{
	const int DIRECTION = 1;
	const int VELOCITY = 2;
}

namespace INKY_INITIAL_INFO
{
	const int DIRECTION = 0;
	const int VELOCITY = 2;
}

namespace CLYDE_INITIAL_INFO
{
	const int DIRECTION = 1;
	const int VELOCITY = 2;
}

namespace POWER_UP_INFO
{
	const int VELOCITY = 1;
	const int X_GREY_1_SPRITE = 0;
	const int X_GREY_2_SPRITE = 1;
	const int X_BLUE_1_SPRITE = 2;
	const int X_BLUE_2_SPRITE = 3;
	const int Y_SPRITE_POSITION = 4;
}

namespace HUD_INFO
{
	const int X_BACKGROUND = 7;
	const int Y_BACKGROUND = 6;
	const int X_STRAWBERRY = 1;
	const int Y_STRAWBERRY = 6;
	const int STRAWBERRY_SIZE = 70;
	const int INITIAL_STRAWBERRY_X = 705;
	const int INITIAL_STRAWBERRY_Y = 265;
	const int X_CHERRY = 0;
	const int Y_CHERRY = 6;
	const int CHERRY_SIZE = 70;
	const int INITIAL_CHERRY_X = 705;
	const int INITIAL_CHERRY_Y = 195;
	const int X_ORANGE = 2;
	const int Y_ORANGE = 6;
	const int ORANGE_SIZE = 70;
	const int INITIAL_ORANGE_X = 705;
	const int INITIAL_ORANGE_Y = 335;
	const int X_LIVE = 7;
	const int Y_LIVE = 0;
	const int LIVE_SIZE = 70;
	const int INITIAL_LIVE_X = 695;
	const int INITIAL_LIVE_Y = 600;
	const int SCORE_W = 40;
	const int SCORE_H = 80;
	const int SCORE_INITIAL_X = 710;
	const int SCORE_INITIAL_Y = 50;
	const int X_TRANSPARENT = 0;
	const int Y_TRANSPARENT = 7;
	const int X_NULL = 3;
	const int Y_NULL = 6;
}

namespace SCORE_0
{
	const std::string ID = "SCORE_0";
	const std::string TEXT = "0";
	const Color COLOR = Color(0, 0, 0, 255);
}

namespace SCORE_1
{
	const std::string ID = "SCORE_1";
	const std::string TEXT = "1";
	const Color COLOR = Color(0, 0, 0, 255);
}

namespace SCORE_2
{
	const std::string ID = "SCORE_2";
	const std::string TEXT = "2";
	const Color COLOR = Color(0, 0, 0, 255);
}

namespace SCORE_3
{
	const std::string ID = "SCORE_3";
	const std::string TEXT = "3";
	const Color COLOR = Color(0, 0, 0, 255);
}

namespace SCORE_4
{
	const std::string ID = "SCORE_4";
	const std::string TEXT = "4";
	const Color COLOR = Color(0, 0, 0, 255);
}

namespace SCORE_5
{
	const std::string ID = "SCORE_5";
	const std::string TEXT = "5";
	const Color COLOR = Color(0, 0, 0, 255);
}

namespace SCORE_6
{
	const std::string ID = "SCORE_6";
	const std::string TEXT = "6";
	const Color COLOR = Color(0, 0, 0, 255);
}

namespace SCORE_7
{
	const std::string ID = "SCORE_7";
	const std::string TEXT = "7";
	const Color COLOR = Color(0, 0, 0, 255);
}

namespace SCORE_8
{
	const std::string ID = "SCORE_8";
	const std::string TEXT = "8";
	const Color COLOR = Color(0, 0, 0, 255);
}

namespace SCORE_9
{
	const std::string ID = "SCORE_9";
	const std::string TEXT = "9";
	const Color COLOR = Color(0, 0, 0, 255);
}

namespace PRESS_SPACE1
{
	const std::string ID = "Start Game Button1";
	const std::string TEXT = "PrEs SpAcE";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 385;
	const int H = 60;
	const int X = 200;
	const int Y = 250;
}

namespace PRESS_SPACE2
{
	const std::string ID = "Start Game Button2";
	const std::string TEXT = "tO sTaRt........";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 385;
	const int H = 60;
	const int X = 200;
	const int Y = 325;
}

namespace STOP_PRESS_SPACE1
{
	const std::string ID = "Stop Button1";
	const std::string TEXT = "StOp";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 385;
	const int H = 100;
	const int X = 200;
	const int Y = 50;
}

namespace STOP_PRESS_SPACE2
{
	const std::string ID = "Stop Button2";
	const std::string TEXT = "PrEs SpAcE";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 385;
	const int H = 60;
	const int X = 200;
	const int Y = 175;
}

namespace STOP_PRESS_SPACE3
{
	const std::string ID = "Stop Button3";
	const std::string TEXT = "tO rElEaCe";
	const Color COLOR = Color(255, 0, 0, 255);
	const int W = 385;
	const int H = 60;
	const int X = 200;
	const int Y = 250;
}

namespace SOUND_PAUSE
{
	const std::string ID = "Sound Pause";
	const std::string TEXT = "SoUnD oN";
	const Color COLOR = Color(255, 255, 255, 255);
	const int W = 275;
	const int H = 50;
	const int X = 250;
	const int Y = 400;
}

namespace NULL_TEXT
{
	const std::string ID = "Null Text";
	const std::string TEXT = " ";
	const Color COLOR = Color(0, 0, 0, 0);
	const int W = 350;
	const int H = 50;
	const int X = 285;
	const int Y = 375;
}