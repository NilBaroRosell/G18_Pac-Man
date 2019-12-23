#pragma once
#include "SceneManager.h"
#include "Button.h"

class Ranking : public SceneManager
{
private:
	Button backButton;
	Rect* rankingRect;
	bool CheckRankingCreated();
	void CreateRanking(PlayerRankingInfo _info);
	void ReadRanking();
	void CheckNewPlayerRankingInfo(PlayerRankingInfo _info);
	void OrderRanking();
	void WriteRanking();
	void Print();
	std::vector<PlayerRankingInfo> ranking;
public:
	Ranking();
	Ranking(PlayerRankingInfo _info);
	void Update(bool * _keys, Vec2 _mousePosition);
	PlayerRankingInfo GetPlayerRankingInfo();
	void Draw();
	~Ranking();
};

