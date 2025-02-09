#include "Play.h"

Play::Play()
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
	soundtrack = Mix_LoadMUS("../../res/au/Pac-Man-Theme-Song.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
	Mix_PlayMusic(soundtrack, -1);
	ReadConfig();
	state = SceneStates::START_GAME_PLAY;
	powerUpEffect = false;
	fruitTimeDown = 10.0f;
	fruitLastTime = clock();
	lastFruits[0] = 0;
	lastFruits[1] = 0;
	createFruit = true;
}

void Play::ReadConfig()
{
	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node<> *pRoot = doc.first_node();
	rapidxml::xml_node<> *pNode = pRoot->first_node("Positions");

	rapidxml::xml_attribute<> *pAttr = pNode->first_attribute();
	sizeX = std::atoi(pAttr->value());
	map = new char*[std::atoi(pAttr->value())];
	ghostsMap = new char*[std::atoi(pAttr->value())];
	pAttr = pAttr->next_attribute();
	sizeY = std::atoi(pAttr->value());
	for (int i = 0; i < sizeX; i++)
	{
		map[i] = new char[std::atoi(pAttr->value())];
		ghostsMap[i] = new char[std::atoi(pAttr->value())];
		for (int j = 0; j < sizeY; j++)
		{
			map[i][j] = ' ';
			ghostsMap[i][j] = ' ';
		}
	}
	
	//player
	rapidxml::xml_node<> *pNodeI = pNode->first_node("Player");
	pAttr = pNodeI->first_attribute();
	player.objectId = PACMAN_SPRITESHEET::ID;
	player.objectRect = Rect{ (std::atoi(pAttr->value()) - 1) * SIZE , (std::atoi(pAttr->next_attribute()->value()) - 1) * SIZE, SIZE, SIZE };
	player.objectSpriteRect = Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * PLAYER::X_RIGHT_CLOSE_SPRITE , (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * PLAYER::Y_SPRITE_POSITION, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE };
	player.actualPosition.x = std::atoi(pAttr->value()) - 1;
	player.actualPosition.y = std::atoi(pAttr->next_attribute()->value()) - 1;
	player.SetInitialPosition(player.actualPosition.x, player.actualPosition.y);
	map[std::atoi(pAttr->value()) - 1][std::atoi(pAttr->next_attribute()->value()) - 1] = 'X';
	
	//blinky
	pNodeI = pNodeI->next_sibling();
	pAttr = pNodeI->first_attribute();
	blinky.objectId = PACMAN_SPRITESHEET::ID;
	blinky.objectRect = Rect{ (std::atoi(pAttr->value()) - 1) * SIZE , (std::atoi(pAttr->next_attribute()->value()) - 1) * SIZE, SIZE, SIZE };
	blinky.objectSpriteRect = Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * BLINKY::X_UP_CLOSE_SPRITE , (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * BLINKY::Y_SPRITE_POSITION, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE };
	blinky.actualPosition.x = std::atoi(pAttr->value()) - 1;
	blinky.actualPosition.y = std::atoi(pAttr->next_attribute()->value()) - 1;
	blinky.SetInitialPosition(blinky.actualPosition.x, blinky.actualPosition.y);
	map[std::atoi(pAttr->value()) - 1][std::atoi(pAttr->next_attribute()->value()) - 1] = 'B';
	ghostsMap[std::atoi(pAttr->value()) - 1][std::atoi(pAttr->next_attribute()->value()) - 1] = 'B';
	
	//inky
	pNodeI = pNodeI->next_sibling();
	pAttr = pNodeI->first_attribute();
	inky.objectId = PACMAN_SPRITESHEET::ID;
	inky.objectRect = Rect{ (std::atoi(pAttr->value()) - 1) * SIZE , (std::atoi(pAttr->next_attribute()->value()) - 1) * SIZE, SIZE, SIZE };
	inky.objectSpriteRect = Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * INKY::X_UP_CLOSE_SPRITE , (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * INKY::Y_SPRITE_POSITION, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE };
	inky.actualPosition.x = std::atoi(pAttr->value()) - 1;
	inky.actualPosition.y = std::atoi(pAttr->next_attribute()->value()) - 1;
	inky.SetInitialPosition(inky.actualPosition.x, inky.actualPosition.y);
	map[std::atoi(pAttr->value()) - 1][std::atoi(pAttr->next_attribute()->value()) - 1] = 'I';
	ghostsMap[std::atoi(pAttr->value()) - 1][std::atoi(pAttr->next_attribute()->value()) - 1] = 'I';
	
	//clyde
	pNodeI = pNodeI->next_sibling();
	pAttr = pNodeI->first_attribute();
	clyde.objectId = PACMAN_SPRITESHEET::ID;
	clyde.objectRect = Rect{ (std::atoi(pAttr->value()) - 1) * SIZE , (std::atoi(pAttr->next_attribute()->value()) - 1) * SIZE, SIZE, SIZE };
	clyde.objectSpriteRect = Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * CLYDE::X_UP_CLOSE_SPRITE , (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * CLYDE::Y_SPRITE_POSITION, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE };
	clyde.actualPosition.x = std::atoi(pAttr->value()) - 1;
	clyde.actualPosition.y = std::atoi(pAttr->next_attribute()->value()) - 1;
	clyde.SetInitialPosition(clyde.actualPosition.x, clyde.actualPosition.y);
	map[std::atoi(pAttr->value()) - 1][std::atoi(pAttr->next_attribute()->value()) - 1] = 'C';
	ghostsMap[std::atoi(pAttr->value()) - 1][std::atoi(pAttr->next_attribute()->value()) - 1] = 'C';
	
	//powerups
	for (pNodeI = pNodeI->next_sibling()->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
	{
		pAttr = pNodeI->first_attribute();
		map[std::atoi(pAttr->value()) - 1][std::atoi(pAttr->next_attribute()->value()) - 1] = 'o';
	}

	//walls
	pNode = pNode->next_sibling();
	for (pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
	{
		pAttr = pNodeI->first_attribute();
		map[std::atoi(pAttr->value()) - 1][std::atoi(pAttr->next_attribute()->value()) - 1] = 'W';
		ghostsMap[std::atoi(pAttr->value()) - 1][std::atoi(pAttr->next_attribute()->value()) - 1] = 'W';
	}

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			if (map[i][j] == ' ')
			{
				map[i][j] = 'P';
			}
			else if (map[i][j] == 'B' || map[i][j] == 'I' || map[i][j] == 'C')
			{
				map[i][j] = ' ';
			}
		}
	}
}

void Play::Update(bool * _keys, Vec2 _mousePosition)
{
	switch (state)
	{
		case START_GAME_PLAY:
			if (_keys[(int)InputKey::K_SPACE])
			{
				state = RUNNING_PLAY;
				hud.DisableStart();
			}
			break;
		case RUNNING_PLAY:
			if (_keys[(int)InputKey::K_P])
			{
				system("CLS");
				for (int i = 0; i < sizeX; i++)
				{
					for (int j = 0; j < sizeY; j++)
					{
						std::cout << ghostsMap[j][i];
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
				/*state = PAUSED_PLAY;
				hud.EnablePause();*/
			}
			else
			{
				CheckBlinkyDirections();
				blinky.Update();
				inky.Update(_keys);
				clyde.Update(_keys);
				player.Update(_keys);
				hud.Update();
				CheckGhostsCollisions();
				CheckPlayerCollisions();
				if (powerUpEffect)
				{
					powerDeltaTime = (clock() - powerLastTime);
					powerLastTime = clock();
					powerDeltaTime /= CLOCKS_PER_SEC;
					powerTimeDown -= powerDeltaTime;
				}
				if (powerTimeDown <= 0) powerUpEffect = false;
				fruitDeltaTime = (clock() - fruitLastTime);
				fruitLastTime = clock();
				fruitDeltaTime /= CLOCKS_PER_SEC;
				fruitTimeDown -= fruitDeltaTime;
				if (fruitTimeDown <= 0 && createFruit)
				{
					if (player.actualPosition.x == player.initialPosition.x && player.actualPosition.y == player.initialPosition.y)
					{
						fruitTimeDown = 2.0f;
						createFruit = true;
					}
					else
					{
						GetRandomFruit();
						switch (lastFruits[1])
						{
						case 1:
							map[player.initialPosition.x][player.initialPosition.y] = 'S';
							break;
						case 2:
							map[player.initialPosition.x][player.initialPosition.y] = 'C';
							break;
						case 3:
							map[player.initialPosition.x][player.initialPosition.y] = 'O';
							break;
						default:
							break;
						}
						createFruit = false;
					}
				}
				if (player.lives <= 0)
				{
					state = GAME_OVER_PLAY;
					std::cout << "Please, enter your name here: ";
				}
				if (CheckGameOver())
				{
					state = GAME_OVER_PLAY;
					std::cout << "Please, enter your name here: ";
				}
			}
			break;
		case PAUSED_PLAY:
			hud.hudSound.Update(_keys[(int)InputKey::K_MOUSE], _mousePosition);
			if (_keys[(int)InputKey::K_SPACE])
			{
				state = RUNNING_PLAY;
				hud.DisablePause();
			}
			else if (_keys[(int)InputKey::K_ESC]) state = GAME_OVER_PLAY;
			if (hud.hudSound.isPressed)
			{
				if (Mix_PlayingMusic())
				{
					Mix_HaltMusic();
				}
				else
				{
					Mix_PlayMusic(soundtrack, -1);
				}
			}
			break;
		case GAME_OVER_PLAY:
			break;
		default:
			break;
	}
}

void Play::CheckBlinkyDirections()
{
	switch (blinky.direction)
	{
	case 0:
		if(blinky.objectRect.x <= 1) blinky.directions[0] = ghostsMap[sizeX-1][blinky.actualPosition.y] != 'W';
		else blinky.directions[0] = ghostsMap[blinky.actualPosition.x - 1][blinky.actualPosition.y] != 'W';
		blinky.directions[1] = false;
		blinky.directions[2] = ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y - 1] != 'W';
		blinky.directions[3] = ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y + 1] != 'W';
		break;
	case 1:
		blinky.directions[0] = false;
		if (blinky.objectRect.x >= SIZE * 19 - 1) blinky.directions[1] = ghostsMap[0][blinky.actualPosition.y] != 'W';
		else blinky.directions[1] = ghostsMap[blinky.actualPosition.x + 1][blinky.actualPosition.y] != 'W';
		blinky.directions[2] = ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y - 1] != 'W';
		blinky.directions[3] = ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y + 1] != 'W';
		break;
	case 2:
		blinky.directions[0] = ghostsMap[blinky.actualPosition.x - 1][blinky.actualPosition.y] != 'W';
		blinky.directions[1] = ghostsMap[blinky.actualPosition.x + 1][blinky.actualPosition.y] != 'W';
		if (blinky.objectRect.y <= 1)blinky.directions[2] = ghostsMap[blinky.actualPosition.x][sizeY - 1] != 'W';
		else blinky.directions[2] = ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y - 1] != 'W';
		blinky.directions[3] = false;
		break;
	case 3:
		blinky.directions[0] = ghostsMap[blinky.actualPosition.x - 1][blinky.actualPosition.y] != 'W';
		blinky.directions[1] = ghostsMap[blinky.actualPosition.x + 1][blinky.actualPosition.y] != 'W';
		blinky.directions[2] = false;
		if (blinky.objectRect.y >= SIZE * 19 - 1)blinky.directions[3] = ghostsMap[blinky.actualPosition.x][0] != 'W';
		else blinky.directions[3] = ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y + 1] != 'W';
		break;
	default:
		break;
	}
}

int Play::GetRandomNum()
{
	return rand() % 3 + 1;
}

void Play::GetRandomFruit()
{
	if (lastFruits[0] == 0 || lastFruits[0] != lastFruits[1])
	{
		lastFruits[0] = lastFruits[1];
		lastFruits[1] = GetRandomNum(); 
	}
	else
	{
		while (true)
		{
			lastFruits[1] = GetRandomNum();
			if (lastFruits[1] != lastFruits[0])
			{
				break;
			}
		}
	}
}

void Play::CheckPlayerCollisions()
{
	switch (player.direction)
	{
		case 0:
			if (player.objectRect.x <= 3)
			{
				CheckLeft();
			}
			else if(map[player.actualPosition.x - 1][player.actualPosition.y] != 'W')
			{
				CheckLeft();
			}
			
			if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'B')
			{
				if (powerUpEffect)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.Respawn();
					player.AddPoints(blinky.points);
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = 'B';
				}
				else PlayerDead();
			}
			else if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'I')
			{
				if (powerUpEffect)
				{
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = ' ';
					inky.Respawn();
					player.AddPoints(inky.points);
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = 'I';
				}
				else PlayerDead();
			}
			else if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'C')
			{
				if (powerUpEffect)
				{
					ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = ' ';
					clyde.Respawn();
					player.AddPoints(clyde.points);
					ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = 'C';
				}
				else PlayerDead();
			}
			break;
		case 1:
			if (player.objectRect.x >=  SIZE * 19 - 3)
			{
				CheckRight();
			}
			else if (map[player.actualPosition.x + 1][player.actualPosition.y] != 'W')
			{
				CheckRight();
			}
			
			if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'B')
			{
				if (powerUpEffect)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.Respawn();
					player.AddPoints(blinky.points);
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = 'B';
				}
			}
			else if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'I')
			{
				if (powerUpEffect)
				{
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = ' ';
					inky.Respawn();
					player.AddPoints(inky.points);
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = 'I';
				}
				else PlayerDead();
			}
			else if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'C')
			{
				if (powerUpEffect)
				{
					ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = ' ';
					clyde.Respawn();
					player.AddPoints(clyde.points);
					ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = 'C';
				}
				else PlayerDead();
			}
			break;
		case 2:
			if (player.objectRect.y <= 3)
			{
				CheckUp();
			}
			else if (map[player.actualPosition.x][player.actualPosition.y - 1] != 'W')
			{
				CheckUp();
			}
			
			if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'B')
			{
				if (powerUpEffect)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.Respawn();
					player.AddPoints(blinky.points);
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = 'B';
				}
				else PlayerDead();
			}
			else if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'I')
			{
				if (powerUpEffect)
				{
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = ' ';
					inky.Respawn();
					player.AddPoints(inky.points);
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = 'I';
				}
				else PlayerDead();
			}
			else if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'C')
			{
				if (powerUpEffect)
				{
					ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = ' ';
					clyde.Respawn();
					player.AddPoints(clyde.points);
					ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = 'C';
				}
				else PlayerDead();
			}
			break;
		case 3:
			if (player.objectRect.y >= SIZE * 19 - 3)
			{
				CheckDown();
			}
			else if (map[player.actualPosition.x][player.actualPosition.y + 1] != 'W')
			{
				CheckDown();
			}
			
			if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'B')
			{
				if (powerUpEffect)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.Respawn();
					player.AddPoints(blinky.points);
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = 'B';
				}
				else PlayerDead();
			}
			else if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'I')
			{
				if (powerUpEffect)
				{
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = ' ';
					inky.Respawn();
					player.AddPoints(inky.points);
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = 'I';
				}
				else PlayerDead();
			}
			else if (ghostsMap[player.actualPosition.x][player.actualPosition.y] == 'C')
			{
				if (powerUpEffect)
				{
					ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = ' ';
					clyde.Respawn();
					player.AddPoints(clyde.points);
					ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = 'C';
				}
				else PlayerDead();
			}
			break;
		default:
			break;
	}	

	map[player.actualPosition.x][player.actualPosition.y] = 'X';
	player.lastDirection = player.direction;
}

void Play::CheckLeft()
{
	if (player.objectRect.x <= 3)
	{
		if (map[sizeX-1][player.actualPosition.y] != 'W')
		{
			player.Move();
		}
	}
	else
	{
		if (player.direction != player.lastDirection)
		{
			if (player.objectRect.x % SIZE <= 1)
			{
				player.Move();
				player.objectRect.y = player.actualPosition.y * SIZE;
			}
		}
		else
		{
			player.Move();
		}

		if (player.objectRect.x % SIZE == 3)
		{
			map[player.actualPosition.x][player.actualPosition.y] = ' ';
			player.objectRect.x--;
			if (map[player.actualPosition.x - 1][player.actualPosition.y] == 'P')
			{
				player.AddPoints(POINT_DATA::POINTS);
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x - 1][player.actualPosition.y] == 'o')
			{
				player.AddPoints(POWERUP_DATA::POINTS);
				hud.UpdateScoreInfo(player.score);
				powerUpEffect = true;
				powerLastTime = clock();
				powerTimeDown = 10;
			}
			if (map[player.actualPosition.x - 1][player.actualPosition.y] == 'S')
			{
				player.AddPoints(STRAWBERRY_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.strawberryCount < 9) hud.strawberryCount++;
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x - 1][player.actualPosition.y] == 'C')
			{
				player.AddPoints(CHERRY_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.cherryCount < 9) hud.cherryCount++;
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x - 1][player.actualPosition.y] == 'O')
			{
				player.AddPoints(ORANGE_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.orangeCount < 9) hud.orangeCount++;
				hud.UpdateScoreInfo(player.score);
			}

			player.actualPosition.x--;
		}
	}
}

void Play::CheckRight()
{
	if (player.objectRect.x >= SIZE * 19 - 3)
	{
		if (map[0][player.actualPosition.y] != 'W')
		{
			player.Move();
		}
	}
	else
	{
		if (player.direction != player.lastDirection)
		{
			if (player.objectRect.x % SIZE <= SIZE - 1)
			{
				player.Move();
				player.objectRect.y = player.actualPosition.y * SIZE;
			}
		}
		else
		{
			player.Move();
		}

		if (player.objectRect.x % SIZE == SIZE - 3)
		{
			map[player.actualPosition.x][player.actualPosition.y] = ' ';
			player.objectRect.x++;

			if (map[player.actualPosition.x + 1][player.actualPosition.y] == 'P')
			{
				player.AddPoints(POINT_DATA::POINTS);
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x + 1][player.actualPosition.y] == 'o')
			{
				player.AddPoints(POWERUP_DATA::POINTS);
				hud.UpdateScoreInfo(player.score);
				powerUpEffect = true;
				powerLastTime = clock();
				powerTimeDown = 10;
			}
			if (map[player.actualPosition.x + 1][player.actualPosition.y] == 'S')
			{
				player.AddPoints(STRAWBERRY_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.strawberryCount < 9) hud.strawberryCount++;
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x + 1][player.actualPosition.y] == 'C')
			{
				player.AddPoints(CHERRY_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.cherryCount < 9) hud.cherryCount++;
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x + 1][player.actualPosition.y] == 'O')
			{
				player.AddPoints(ORANGE_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.orangeCount < 9) hud.orangeCount++;
				hud.UpdateScoreInfo(player.score);
			}

			player.actualPosition.x++;
		}
	}
}

void Play::CheckUp()
{
	if (player.objectRect.y <= 3)
	{
		if (map[player.actualPosition.x][sizeY - 1] != 'W')
		{
			player.Move();
		}
	}
	else
	{
		if (player.direction != player.lastDirection)
		{
			if (player.objectRect.y % SIZE <= 1)
			{
				player.Move();
				player.objectRect.x = player.actualPosition.x * SIZE;
			}
		}
		else
		{
			player.Move();
		}

		if (player.objectRect.y % SIZE == 3)
		{
			map[player.actualPosition.x][player.actualPosition.y] = ' ';
			player.objectRect.y--;

			if (map[player.actualPosition.x][player.actualPosition.y - 1] == 'P')
			{
				player.AddPoints(POINT_DATA::POINTS);
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x][player.actualPosition.y - 1] == 'o')
			{
				player.AddPoints(POWERUP_DATA::POINTS);
				hud.UpdateScoreInfo(player.score);
				powerUpEffect = true;
				powerLastTime = clock();
				powerTimeDown = 10;
			}
			if (map[player.actualPosition.x][player.actualPosition.y - 1] == 'S')
			{
				player.AddPoints(STRAWBERRY_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.strawberryCount < 9) hud.strawberryCount++;
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x][player.actualPosition.y - 1] == 'C')
			{
				player.AddPoints(CHERRY_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.cherryCount < 9) hud.cherryCount++;
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x][player.actualPosition.y - 1] == 'O')
			{
				player.AddPoints(ORANGE_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.orangeCount < 9) hud.orangeCount++;
				hud.UpdateScoreInfo(player.score);
			}

			player.actualPosition.y--;
		}
	}
}

void Play::CheckDown()
{
	if (player.objectRect.y >= SIZE * 19 - 3)
	{
		if (map[player.actualPosition.x][0] != 'W')
		{
			player.Move();
		}
	}
	else
	{
		if (player.direction != player.lastDirection)
		{
			if (player.objectRect.y % SIZE <= SIZE - 1)
			{
				player.Move();
				player.objectRect.x = player.actualPosition.x * SIZE;
			}
		}
		else
		{
			player.Move();
		}
		
		if (player.objectRect.y % SIZE == SIZE - 3)
		{
			map[player.actualPosition.x][player.actualPosition.y] = ' ';
			player.objectRect.y++;

			if (map[player.actualPosition.x][player.actualPosition.y + 1] == 'P')
			{
				player.AddPoints(POINT_DATA::POINTS);
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x][player.actualPosition.y + 1] == 'o')
			{
				player.AddPoints(POWERUP_DATA::POINTS);
				hud.UpdateScoreInfo(player.score);
				powerUpEffect = true;
				powerLastTime = clock();
				powerTimeDown = 10;
			}
			if (map[player.actualPosition.x][player.actualPosition.y + 1] == 'S')
			{
				player.AddPoints(STRAWBERRY_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.strawberryCount < 9) hud.strawberryCount++;
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x][player.actualPosition.y + 1] == 'C')
			{
				player.AddPoints(CHERRY_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.cherryCount < 9) hud.cherryCount++;
				hud.UpdateScoreInfo(player.score);
			}
			if (map[player.actualPosition.x][player.actualPosition.y + 1] == 'O')
			{
				player.AddPoints(ORANGE_DATA::POINTS);
				fruitTimeDown = 15.0f;
				fruitLastTime = clock();
				createFruit = true;
				if (hud.orangeCount < 9) hud.orangeCount++;
				hud.UpdateScoreInfo(player.score);
			}

			player.actualPosition.y++;
		}
	}
}

void Play::PlayerDead()
{
	map[player.actualPosition.x][player.actualPosition.y] = ' ';
	ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
	ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = ' ';
	ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = ' ';
	player.Respawn();
	blinky.Respawn();
	inky.Respawn();
	clyde.Respawn();
	map[player.actualPosition.x][player.actualPosition.y] = 'X';
	ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = 'B';
	ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = 'I';
	ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = 'C';
}

void Play::CheckGhostsCollisions()
{
	switch (blinky.direction)
	{
	case 0:
		if (blinky.objectRect.x <= 1)
		{
			if (ghostsMap[sizeX - 1][blinky.actualPosition.y] != 'W')
			{
				if (powerUpEffect) blinky.Move(POWER_UP_INFO::VELOCITY);
				else blinky.Move(BLINKY_INITIAL_INFO::VELOCITY);
			}
		}
		else if (ghostsMap[blinky.actualPosition.x - 1][blinky.actualPosition.y] != 'W')
		{
			if (powerUpEffect)
			{
				blinky.Move(POWER_UP_INFO::VELOCITY);
				if (blinky.objectRect.x % SIZE == 1)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.objectRect.x--;
					blinky.actualPosition.x--;
				}
			}
			else
			{
				blinky.Move(BLINKY_INITIAL_INFO::VELOCITY);
				if (blinky.objectRect.x % SIZE == 1)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.objectRect.x--;
					blinky.actualPosition.x--;
				}
			}
		}		
		break;
	case 1:
		if (blinky.objectRect.x >= SIZE * 19 - 1)
		{
			if (ghostsMap[0][blinky.actualPosition.y] != 'W')
			{
				if (powerUpEffect) blinky.Move(POWER_UP_INFO::VELOCITY);
				else blinky.Move(BLINKY_INITIAL_INFO::VELOCITY);
			}
		}
		else if (ghostsMap[blinky.actualPosition.x + 1][blinky.actualPosition.y] != 'W')
		{
			if (powerUpEffect)
			{
				blinky.Move(POWER_UP_INFO::VELOCITY);
				if (blinky.objectRect.x % SIZE == SIZE - 1)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.objectRect.x++;
					blinky.actualPosition.x++;
				}
			}
			else
			{
				blinky.Move(BLINKY_INITIAL_INFO::VELOCITY);
				if (blinky.objectRect.x % SIZE == SIZE - 1)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.objectRect.x++;
					blinky.actualPosition.x++;
				}
			}
		}
		break;
	case 2:
		if (blinky.objectRect.y <= 1)
		{
			if (ghostsMap[blinky.actualPosition.x][sizeY - 1] != 'W')
			{
				if (powerUpEffect) blinky.Move(POWER_UP_INFO::VELOCITY);
				else blinky.Move(BLINKY_INITIAL_INFO::VELOCITY);
			}
		}
		else if (ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y - 1] != 'W')
		{
			if (powerUpEffect)
			{
				blinky.Move(POWER_UP_INFO::VELOCITY);
				if (blinky.objectRect.y % SIZE == 1)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.objectRect.y--;
					blinky.actualPosition.y--;
				}
			}
			else
			{
				blinky.Move(BLINKY_INITIAL_INFO::VELOCITY);
				if (blinky.objectRect.y % SIZE == 1)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.objectRect.y--;
					blinky.actualPosition.y--;
				}
			}
		}
		break;
	case 3:
		if (blinky.objectRect.y >= SIZE * 19 - 1)
		{
			if (ghostsMap[blinky.actualPosition.x][0] != 'W')
			{
				if (powerUpEffect) blinky.Move(POWER_UP_INFO::VELOCITY);
				else blinky.Move(BLINKY_INITIAL_INFO::VELOCITY);
			}
		}
		else if (ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y + 1] != 'W')
		{
			if (powerUpEffect)
			{
				blinky.Move(POWER_UP_INFO::VELOCITY);
				if (blinky.objectRect.y % SIZE == SIZE - 1)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.objectRect.y++;
					blinky.actualPosition.y++;
				}
			}
			else
			{
				blinky.Move(BLINKY_INITIAL_INFO::VELOCITY);
				if (blinky.objectRect.y % SIZE == SIZE - 1)
				{
					ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = ' ';
					blinky.objectRect.y++;
					blinky.actualPosition.y++;
				}
			}
		}
		break;
	default:
		break;
	}
	ghostsMap[blinky.actualPosition.x][blinky.actualPosition.y] = 'B';
	blinky.lastDirection = blinky.direction;

	switch (inky.direction)
	{
		case 0:
			if (inky.objectRect.x <= 3)
			{
				if (ghostsMap[sizeX - 1][inky.actualPosition.y] != 'W')
				{
					if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
					else inky.Move(INKY_INITIAL_INFO::VELOCITY);
				}
			}
			else if(ghostsMap[inky.actualPosition.x - 1][inky.actualPosition.y] != 'W')
			{
				if (inky.direction != inky.lastDirection)
				{
					if (inky.objectRect.x % SIZE <= 1)
					{
						if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
						else inky.Move(INKY_INITIAL_INFO::VELOCITY);
					}
				}
				else
				{
					if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
					else inky.Move(INKY_INITIAL_INFO::VELOCITY);
				}
				inky.objectRect.y = inky.actualPosition.y * SIZE;
				if (inky.objectRect.x % SIZE == 1)
				{
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = ' ';
					inky.objectRect.x--;
					inky.actualPosition.x--;
				}
			}
			break;
		case 1:
			if (inky.objectRect.x >= SIZE * 19 - 1)
			{
				if (ghostsMap[0][inky.actualPosition.y] != 'W')
				{
					if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
					else inky.Move(INKY_INITIAL_INFO::VELOCITY);
				}
			}
			else if (ghostsMap[inky.actualPosition.x + 1][inky.actualPosition.y] != 'W')
			{
				if (inky.direction != inky.lastDirection)
				{
					if (inky.objectRect.x % SIZE >= SIZE - 1)
					{
						if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
						else inky.Move(INKY_INITIAL_INFO::VELOCITY);
					}
				}
				else
				{
					if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
					else inky.Move(INKY_INITIAL_INFO::VELOCITY);
				}
				inky.objectRect.y = inky.actualPosition.y * SIZE;
				if (inky.objectRect.x % SIZE == SIZE - 1)
				{
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = ' ';
					inky.objectRect.x++;
					inky.actualPosition.x++;
				}
			}
			break;
		case 2:
			if (inky.objectRect.y <= 3)
			{
				if (ghostsMap[inky.actualPosition.x][sizeY - 1] != 'W')
				{
					if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
					else inky.Move(INKY_INITIAL_INFO::VELOCITY);
				}
			}
			else if (ghostsMap[inky.actualPosition.x][inky.actualPosition.y - 1] != 'W')
			{
				if (inky.direction != inky.lastDirection)
				{
					if (inky.objectRect.y % SIZE <= 1)
					{
						if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
						else inky.Move(INKY_INITIAL_INFO::VELOCITY);
					}
				}
				else
				{
					if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
					else inky.Move(INKY_INITIAL_INFO::VELOCITY);
				}
				inky.objectRect.x = inky.actualPosition.x * SIZE;
				if (inky.objectRect.y % SIZE == 1)
				{
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = ' ';
					inky.objectRect.y--;
					inky.actualPosition.y--;
				}
			}
			break;
		case 3:
			if (inky.objectRect.y >= SIZE * 19 - 1)
			{
				if (ghostsMap[inky.actualPosition.x][0] != 'W')
				{
					if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
					else inky.Move(INKY_INITIAL_INFO::VELOCITY);
				}
			}
			else if (ghostsMap[inky.actualPosition.x][inky.actualPosition.y + 1] != 'W')
			{
				if (inky.direction != inky.lastDirection)
				{
					if (inky.objectRect.y % SIZE >= SIZE - 1)
					{
						if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
						else inky.Move(INKY_INITIAL_INFO::VELOCITY);
					}
				}
				else
				{
					if (powerUpEffect) inky.Move(POWER_UP_INFO::VELOCITY);
					else inky.Move(INKY_INITIAL_INFO::VELOCITY);
				}
				inky.objectRect.x = inky.actualPosition.x * SIZE;
				if (inky.objectRect.y % SIZE == SIZE - 1)
				{
					ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = ' ';
					inky.objectRect.y++;
					inky.actualPosition.y++;
				}
			}
			break;
		default:
			break;
	}
	ghostsMap[inky.actualPosition.x][inky.actualPosition.y] = 'I';
	inky.lastDirection = inky.direction;

	switch (clyde.direction)
	{
	case 0:
		if (clyde.objectRect.x <= 3)
		{
			if (ghostsMap[sizeX - 1][clyde.actualPosition.y] != 'W')
			{
				if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
				else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
			}
		}
		else if (ghostsMap[clyde.actualPosition.x - 1][clyde.actualPosition.y] != 'W')
		{
			if (clyde.direction != clyde.lastDirection)
			{
				if (clyde.objectRect.x % SIZE <= 1)
				{
					if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
					else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
				}
			}
			else
			{
				if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
				else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
			}
			clyde.objectRect.y = clyde.actualPosition.y * SIZE;
			if (clyde.objectRect.x % SIZE == 1)
			{
				ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = ' ';
				clyde.objectRect.x--;
				clyde.actualPosition.x--;
			}
		}
		break;
	case 1:
		if (clyde.objectRect.x >= SIZE * 19 - 1)
		{
			if (ghostsMap[0][clyde.actualPosition.y] != 'W')
			{
				if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
				else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
			}
		}
		else if (ghostsMap[clyde.actualPosition.x + 1][clyde.actualPosition.y] != 'W')
		{
			if (clyde.direction != clyde.lastDirection)
			{
				if (clyde.objectRect.x % SIZE >= SIZE - 1)
				{
					if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
					else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
				}
			}
			else
			{
				if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
				else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
			}
			clyde.objectRect.y = clyde.actualPosition.y * SIZE;
			if (clyde.objectRect.x % SIZE == SIZE - 1)
			{
				ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = ' ';
				clyde.objectRect.x++;
				clyde.actualPosition.x++;
			}
		}
		break;
	case 2:
		if (clyde.objectRect.y <= 3)
		{
			if (ghostsMap[clyde.actualPosition.x][sizeY - 1] != 'W')
			{
				if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
				else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
			}
		}
		else if (ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y - 1] != 'W')
		{
			if (clyde.direction != clyde.lastDirection)
			{
				if (clyde.objectRect.y % SIZE <= 1)
				{
					if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
					else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
				}
			}
			else
			{
				if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
				else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
			}
			clyde.objectRect.x = clyde.actualPosition.x * SIZE;
			if (clyde.objectRect.y % SIZE == 1)
			{
				ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = ' ';
				clyde.objectRect.y--;
				clyde.actualPosition.y--;
			}
		}
		break;
	case 3:
		if (clyde.objectRect.y >= SIZE * 19 - 1)
		{
			if (ghostsMap[clyde.actualPosition.x][0] != 'W')
			{
				if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
				else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
			}
		}
		else if (ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y + 1] != 'W')
		{
			if (clyde.direction != clyde.lastDirection)
			{
				if (clyde.objectRect.y % SIZE >= SIZE - 1)
				{
					if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
					else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
				}
			}
			else
			{
				if (powerUpEffect) clyde.Move(POWER_UP_INFO::VELOCITY);
				else clyde.Move(CLYDE_INITIAL_INFO::VELOCITY);
			}
			clyde.objectRect.x = clyde.actualPosition.x * SIZE;
			if (clyde.objectRect.y % SIZE == SIZE - 1)
			{
				ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = ' ';
				clyde.objectRect.y++;
				clyde.actualPosition.y++;
			}
		}
		break;
	default:
		break;
	}
	ghostsMap[clyde.actualPosition.x][clyde.actualPosition.y] = 'C';
	clyde.lastDirection = clyde.direction;

	if (powerUpEffect)
	{
		blinky.AnimatePowerUp();
		inky.AnimatePowerUp();
		clyde.AnimatePowerUp();
	}
	else
	{
		blinky.Animate();
		inky.Animate();
		clyde.Animate();
	}
}

bool Play::CheckGameOver()
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			if(map[i][j] == 'o') return false;
			if (map[i][j] == 'P') return false;
		}
	}
	return true;
}

PlayerRankingInfo Play::GetPlayerRankingInfo()
{
	std::string aux;
	std::cin >> aux;
	return { player.score,aux };
}

void Play::Draw()
{
	Renderer::Instance()->SetRendreDrawColor(0, 0, 0);
	Renderer::Instance()->Clear();
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			switch (map[i][j])
			{
				case 'X':
					player.Draw();
					break;
				case 'P':
					Renderer::Instance()->PushSprite(PACMAN_SPRITESHEET::ID, Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * POINT::X_SPRITE_POSITION , (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * POINT::Y_SPRITE_POSITION, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE }, Rect{ i  * SIZE , j * SIZE, SIZE, SIZE });
					break;
				case 'o':
					Renderer::Instance()->PushSprite(PACMAN_SPRITESHEET::ID, Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * POWERUP::X_SPRITE_POSITION , (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * POWERUP::Y_SPRITE_POSITION, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE }, Rect{ i  * SIZE , j * SIZE, SIZE, SIZE });
					break;
				case 'W':
					Renderer::Instance()->PushSprite(PACMAN_SPRITESHEET::ID, Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * WALL::X_SPRITE_POSITION , (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * WALL::Y_SPRITE_POSITION, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE }, Rect{ i  * SIZE , j * SIZE, SIZE, SIZE });
					break;
				case 'S':
					Renderer::Instance()->PushSprite(PACMAN_SPRITESHEET::ID, Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * STRAWBERRY::X_SPRITE_POSITION , (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * STRAWBERRY::Y_SPRITE_POSITION, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE }, Rect{ i  * SIZE , j * SIZE, SIZE, SIZE });
					break;
				case 'C':
					Renderer::Instance()->PushSprite(PACMAN_SPRITESHEET::ID, Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * CHERRY::X_SPRITE_POSITION , (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * CHERRY::Y_SPRITE_POSITION, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE }, Rect{ i  * SIZE , j * SIZE, SIZE, SIZE });
					break;
				case 'O':
					Renderer::Instance()->PushSprite(PACMAN_SPRITESHEET::ID, Rect{ (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * ORANGE::X_SPRITE_POSITION , (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * ORANGE::Y_SPRITE_POSITION, PACMAN_SPRITESHEET::SPRITES_SIZE, PACMAN_SPRITESHEET::SPRITES_SIZE }, Rect{ i  * SIZE , j * SIZE, SIZE, SIZE });
					break;
				default:
					break;
			}
		}
	}	
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			switch (ghostsMap[i][j])
			{
			case 'B':
				blinky.Draw();
				break;
			case 'I':
				inky.Draw();
				break;
			case 'C':
				clyde.Draw();
				break;
			default:
				break;
			}
		}
	}
	hud.Draw(player.lives);
	Renderer::Instance()->Render();
}

Play::~Play()
{
}