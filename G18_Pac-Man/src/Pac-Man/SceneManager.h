#pragma once
#include "Types.h"
#include "Inputs.h"
#include "Constants.h"
#include "Renderer.h"
#include <SDL_mixer.h>
#include <map>

struct PlayerRankingInfo
{
	int score;
	std::string name;
};

class SceneManager
{
protected: 
	Mix_Music* soundtrack;
public:
	SceneStates state;
	SceneManager();
	virtual void Update(bool * _keys, Vec2 _mousePosition) = 0;
	virtual PlayerRankingInfo GetPlayerRankingInfo() = 0;
	virtual void Draw() = 0;
	~SceneManager();
};

