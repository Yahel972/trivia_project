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
	std::vector<Game> getGames();
private:
	IDatabase* m_datebase; // the address of the main database file of the program
	std::vector<Game> m_games; // vectory keeping all of the current active games
};