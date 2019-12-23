#pragma once
#include "Object.h"
#include "Button.h"
class HUD
{
private:
	Object hudBackground;
	Object hudCherry;
	Object hudStrawberry;
	Object hudOrange;
	Object* hudLives;
	std::string* hudScoreID;
	Rect* hudScoreRect;
	std::string hudXID;
	Rect hudXRect[3];
	std::string hudStrawberryID;
	Rect hudStrawberryRect;
	std::string hudCherryID;
	Rect hudCherryRect;
	std::string hudOrangeID;
	Rect hudOrangeRect;
	std::string hudSpaceStartID1;
	Rect hudSpaceStartRect1;
	std::string hudSpaceStartID2;
	Rect hudSpaceStartRect2;
	std::string hudSpacePauseID1;
	Rect hudSpacePauseRect1;
	std::string hudSpacePauseID2;
	Rect hudSpacePauseRect2;
	std::string hudSpacePauseID3;
	Rect hudSpacePauseRect3;
	Object hudTransparent;

public:
	Button hudSound;
	int strawberryCount;
	int cherryCount;
	int orangeCount;
	HUD();
	void Update();
	void UpdateScoreInfo(int _playerScore);
	void DisableStart();
	void EnablePause(); 
	void DisablePause();
	void Draw(int _lives);
	~HUD();
};

