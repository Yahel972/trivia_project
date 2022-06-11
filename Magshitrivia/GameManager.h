#pragma once
#include "Game.h"
#include "SqliteDataBase.h"
#include "Room.h"


class GameManager
{
public:
	GameManager() = default;
	GameManager(IDatabase* datebase);
	Game createGame(Room room);
	void deleteGame();
	std::vector<Game> getGames();
private:
	IDatabase* m_datebase;
	std::vector<Game> m_games;
};