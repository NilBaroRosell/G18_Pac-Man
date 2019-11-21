#pragma once
#include <cstdlib>
#include <iostream>
#include <string>


using Line = struct {
	Line() : a(0), b(0), c(0) {};
	Line(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {};
	int a, b, c;
};

using Rect = struct {
	int x, y;
	int w, h;

	Rect() {};
	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};
	//void SetPosition(Vector2 pos) { x = pos.x; y = pos.y; };
};

using Color = struct {
	int r, g, b, a;
	
	Color() {};
	Color(int _r, int _g, int _b, int _a) : r(_r), g(_g), b(_b), a(_a) {};
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