#pragma once
#include "Game.h"
#include "SqliteDataBase.h"
#include "Room.h"

class GameManager
{
public:
	Game createGame(Room room);
	void deleteGame();
private:
	IDatabase* m_datebase;
	std::vector<Game> m_games;
};