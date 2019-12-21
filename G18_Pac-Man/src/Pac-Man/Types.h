#pragma once
#include <cstdlib>
#include <iostream>
#include <string>

enum class InputKey { QUIT, K_ESC, K_SPACE, K_P, K_MOUSE, K_LEFT, K_RIGHT, K_UP, K_DOWN, COUNT };
enum GameStates { SPLASH_SCREEN, MENU, PLAY, RANKING, EXIT, CURRENT };
enum SceneStates { WAITING_SPLASH, MENU_SPLASH, WAITING_MENU, PLAY_MENU, RANKING_MENU, EXIT_MENU, START_GAME_PLAY, RUNNING_PLAY, PAUSED_PLAY, GAME_OVER_PLAY, WAITING_RANKING, BACK_RANKING };
enum class ElementType { WALL, POINT, POWER_UP, PLAYER, BLINKY, INKY, CLYDE };


struct Vec2
{
	int x;
	int y;
};


struct Line {
	Line() : a(0), b(0), c(0) {};
	Line(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {};
	int a, b, c;
};

struct Rect{
	int x, y;
	int w, h;

	Rect() {};
	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};
	bool checkWallsCollision(Rect _r1, Rect _r2)
	{
		return (((_r1.x - _r2.x) > ((-_r1.w) + 2) && (_r1.x - _r2.x) < (_r1.w - 2)) && ((_r1.y - _r2.y) > ((-_r1.h) + 2) && (_r1.y - _r2.y) < (_r1.h - 2)));
	}
	bool checkGhostCollision(Rect _r1, Rect _r2)
	{
		return (((_r1.x - _r2.x) > ((-_r1.w) + 2) && (_r1.x - _r2.x) < (_r1.w - 2)) && ((_r1.y - _r2.y) > ((-_r1.h) + 2) && (_r1.y - _r2.y) < (_r1.h - 2)));
	}
	bool checkPointsCollision(Rect _r1, Rect _r2)
	{
		return ((_r1.x - _r2.x  > - 7 && _r1.x - _r2.x < 7) && (_r1.y - _r2.y > -7 && _r1.y - _r2.y <7));
	}
	//void SetPosition(Vector2 pos) { x = pos.x; y = pos.y; };
};



struct Color {
	unsigned char r, g, b, a;
	
	Color() {};
	Color(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a) {};
};

using Font = struct {
	std::string id;
	std::string path;
	int size;
};

struct Text {
	std::string id;
	std::string text;
	Color color;
	int w;
	int h;
};