#include "Ranking.h"

Ranking::Ranking()
{
	backButton = Button(BACK_BUTTON::ID, BACK_BUTTON::HOVER_ID, BACK_BUTTON::X, BACK_BUTTON::Y, BACK_BUTTON::W, BACK_BUTTON::H);
	state = SceneStates::WAITING_RANKING;
	if (CheckRankingCreated())
	{
		ReadRanking();
		rankingRect = new Rect[ranking.size()];
		for (int i = 0; i < ranking.size(); i++)
		{
			Text Ranking = { ranking[i].name + std::to_string(ranking[i].score), ranking[i].name + ": " + std::to_string(ranking[i].score), RANKING_INFO::COLOR, RANKING_INFO::WIDTH, RANKING_INFO::HEIGHT };
			Renderer::Instance()->LoadTextureText(PLAY_FONT::ID, Ranking);
			rankingRect[i].x = RANKING_INFO::INITIAL_WIDTH;
			rankingRect[i].y = RANKING_INFO::INITIAL_HEIGHT + i * RANKING_INFO::HEIGHT * 1.5;
			rankingRect[i].w = RANKING_INFO::WIDTH;
			rankingRect[i].h = RANKING_INFO::HEIGHT;
		}
	}

}

Ranking::Ranking(PlayerRankingInfo _info)
{
	backButton = Button(BACK_BUTTON::ID, BACK_BUTTON::HOVER_ID, BACK_BUTTON::X, BACK_BUTTON::Y, BACK_BUTTON::W, BACK_BUTTON::H);
	state = SceneStates::WAITING_RANKING;
	if (CheckRankingCreated())
	{
		ReadRanking();
		CheckNewPlayerRankingInfo(_info);
		rankingRect = new Rect[ranking.size()];
		for (int i = 0; i < ranking.size(); i++)
		{
			Text Ranking = { ranking[i].name + std::to_string(ranking[i].score), ranking[i].name + " : " + std::to_string(ranking[i].score), RANKING_INFO::COLOR, RANKING_INFO::WIDTH, RANKING_INFO::HEIGHT };
			Renderer::Instance()->LoadTextureText(PLAY_FONT::ID, Ranking);
			rankingRect[i].x = RANKING_INFO::INITIAL_WIDTH;
			rankingRect[i].y = RANKING_INFO::INITIAL_HEIGHT + i * RANKING_INFO::HEIGHT * 1.5;
			rankingRect[i].w = RANKING_INFO::WIDTH;
			rankingRect[i].h = RANKING_INFO::HEIGHT;
		}
	}
	else
	{
		CreateRanking(_info);
		rankingRect = new Rect[ranking.size()];
		for (int i = 0; i < ranking.size(); i++)
		{
			Text Ranking = { ranking[i].name + std::to_string(ranking[i].score), ranking[i].name + ": " + std::to_string(ranking[i].score), RANKING_INFO::COLOR, RANKING_INFO::WIDTH, RANKING_INFO::HEIGHT };
			Renderer::Instance()->LoadTextureText(PLAY_FONT::ID, Ranking);
			rankingRect[i].x = RANKING_INFO::INITIAL_WIDTH;
			rankingRect[i].y = RANKING_INFO::INITIAL_HEIGHT + i * RANKING_INFO::HEIGHT * 1.5;
			rankingRect[i].w = RANKING_INFO::WIDTH;
			rankingRect[i].h = RANKING_INFO::HEIGHT;
		}
	}
}

bool Ranking::CheckRankingCreated()
{
	std::ifstream myFile;
	myFile.open("../../res/files/Ranking.bin", std::ios::in | std::ios::binary);
	if (myFile.fail()) return false;
	else return true;
}

void Ranking::CreateRanking(PlayerRankingInfo _info)
{
	std::ofstream newFile;
	newFile.open("../../res/files/Ranking.bin", std::ios::out | std::ios::binary);
	if (newFile.is_open())
	{
		ranking.push_back({ _info.score, _info.name });
		size_t len = ranking.size();
		newFile.write(reinterpret_cast<char *>(&len), sizeof(size_t));
		for (int i = 0; i < ranking.size(); i++)
		{
			len = ranking[i].name.size();
			newFile.write(reinterpret_cast<char *>(&len), sizeof(size_t));
			for (int j = 0; j < ranking[i].name.size(); j++)
			{
				newFile.write(reinterpret_cast<char *>(&ranking[i].name[j]), sizeof(char));
			}
			newFile.write(reinterpret_cast<char *>(&ranking[i].score), sizeof(int));
		}
		newFile.close();
	}
}

void Ranking::ReadRanking()
{
	std::ifstream myFile;
	myFile.open("../../res/files/Ranking.bin", std::ios::in | std::ios::binary);
	if (myFile.is_open())
	{
		size_t len;
		myFile.read(reinterpret_cast<char *>(&len), sizeof(size_t));
		ranking.resize(len);
		for (int i = 0; i < ranking.size(); i++)
		{
			myFile.read(reinterpret_cast<char *>(&len), sizeof(size_t));
			ranking[i].name.resize(len);
			for (int j = 0; j < ranking[i].name.size(); j++)
			{
				myFile.read(reinterpret_cast<char *>(&ranking[i].name[j]), sizeof(char));
			}
			myFile.read(reinterpret_cast<char *>(&ranking[i].score), sizeof(int));
		}
		myFile.close();
	}
}

void Ranking::CheckNewPlayerRankingInfo(PlayerRankingInfo _info)
{
	PlayerRankingInfo aux{ _info.score, _info.name };
	ranking.push_back(aux);
	if (ranking.size() > 5)
	{
		int min = 0;

		for (int i = 0; i < ranking.size(); i++)
		{
			if (ranking[i].score < ranking[min].score)
			{
				min = i;
			}
		}

		OrderRanking();
		ranking.pop_back();
	}
	else OrderRanking();
	WriteRanking();
}

void Ranking::OrderRanking()
{
	for (int i = 0; i < ranking.size(); i++)
	{
		for (int j = i + 1; j < ranking.size(); j++)
		{
			if (ranking[j].score > ranking[i].score)
			{
				PlayerRankingInfo aux { ranking[i].score, ranking[i].name };
				ranking[i].score = ranking[j].score;
				ranking[i].name = ranking[j].name;
				ranking[j].score = aux.score;
				ranking[j].name = aux.name;
			}
		}
	}
}

void Ranking::WriteRanking()
{
	std::ofstream myFile;
	myFile.open("../../res/files/Ranking.bin", std::ios::out | std::ios::binary);
	if (myFile.is_open())
	{
		size_t len = ranking.size();
		myFile.write(reinterpret_cast<char *>(&len), sizeof(size_t));
		for (int i = 0; i < ranking.size(); i++)
		{
			len = ranking[i].name.size();
			myFile.write(reinterpret_cast<char *>(&len), sizeof(size_t));
			for (int j = 0; j < ranking[i].name.size(); j++)
			{
				myFile.write(reinterpret_cast<char *>(&ranking[i].name[j]), sizeof(char));
			}
			myFile.write(reinterpret_cast<char *>(&ranking[i].score), sizeof(int));
		}
		myFile.close();
	}
}

void Ranking::Print()
{
	for (int i = 0; i < ranking.size(); i++)
	{
		std::cout << ranking[i].name << ": " << ranking[i].score << std::endl;
	}
}

void Ranking::Update(bool * _keys, Vec2 _mousePosition)
{
	switch (state)
	{
		case WAITING_RANKING:
			backButton.Update(_keys[(int)InputKey::K_MOUSE], _mousePosition);
			if (backButton.isPressed) state = SceneStates::BACK_RANKING;
			break;
		case BACK_RANKING:
			break;
		default:
			break;
	}
}

PlayerRankingInfo Ranking::GetPlayerRankingInfo()
{
	return { NULL, NULL };
}

void Ranking::Draw()
{
	Renderer::Instance()->SetRendreDrawColor(0, 0, 0);
	Renderer::Instance()->Clear();
	for (int i = 0; i < ranking.size(); i++)
	{
		Renderer::Instance()->PushImage(ranking[i].name + std::to_string(ranking[i].score), rankingRect[i]);
	}
	backButton.Draw();
	Renderer::Instance()->Render();
}

Ranking::~Ranking()
{
}
