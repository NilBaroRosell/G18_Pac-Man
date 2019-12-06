#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include "GameController.h"

int main(int, char*[])
{
	GameController gameController;
	while (gameController.isRunning)
	{
		gameController.Run();
	}

	system("pause");
	return 0;
}