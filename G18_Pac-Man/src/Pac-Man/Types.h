#pragma once
#include <cstdlib>
#include <iostream>
#include <string>

enum class InputKey { K_ESC, K_SPACE, K_P, K_MOUSE, K_LEFT, K_RIGHT, K_UP, K_DOWN, COUNT };

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
	//void SetPosition(Vector2 pos) { x = pos.x; y = pos.y; };
};

struct Color {
	unsigned char r, g, b, a;
	
	Color() {};
	Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : r(_r), g(_g), b(_b), a(_a) {};
};

using Font = struct {
	std::string id;
	std::string path;
	int size;
};

using Text = struct {
	std::string id;
	std::string text;
	Color color;
	int w;
	int h;
};