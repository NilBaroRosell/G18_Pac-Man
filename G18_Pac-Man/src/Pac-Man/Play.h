#pragma once
#include "HUD.h"
#include "SceneManager.h"
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include <sstream> 
#include <string>
#include "Player.h"
#include "Blinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Point.h"
#include "PowerUp.h"
#include <vector>

class Play : public SceneManager
{
private:
	HUD hud;
	int sizeX;
	int sizeY;
	int lastFruits[2]; // 1 = strawberry, 2 = cherry, 3 = orange
	char** map;
	char** ghostsMap;
	bool powerUpEffect;
	bool createFruit;
	float powerDeltaTime;
	clock_t powerLastTime;
	float powerTimeDown;
	float fruitDeltaTime;
	clock_t fruitLastTime;
	float fruitTimeDown;
	Clyde clyde;
	Blinky blinky;
	Inky inky;
	Player player;
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/pacman_beginning.wav") };
	void ReadConfig();
	void CheckLeft();
	void CheckRight();
	void CheckUp();
	void CheckDown();
	void CheckBlinkyDirections();
	int GetRandomNum();
	void GetRandomFruit();
	void PlayerDead();
public:
	Play();
	void Update(bool * _keys, Vec2 _mousePosition);
	void CheckPlayerCollisions();
	void CheckGhostsCollisions();
	bool CheckGameOver();
	PlayerRankingInfo GetPlayerRankingInfo();
	void Draw();
	~Play();
};

