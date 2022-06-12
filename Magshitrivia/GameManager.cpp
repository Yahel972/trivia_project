#include "GameManager.h"

// constructor 
GameManager::GameManager(IDatabase* datebase)
{
    this->m_datebase = datebase;
}

/*
    Function creates a game based on room settings
    Input: the room
    Output: the game
*/
Game GameManager::createGame(Room room)
{
    int numOfQuestion = room.getData().numOfQuestions;
    int id = this->m_datebase->addRoom();
    Game game(this->m_datebase,id, this->m_datebase->getQuestions(numOfQuestion), room.getData().timePerQuestion);
    std::vector<std::string> users = room.getAllUsers();
    for (int i = 0; i < users.size(); i++)
    {
        game.addNewPlayer(LoggedUser(users[i]));
    }
    this->m_games.push_back(game);
    return game;
}

// games getter
std::vector<Game> GameManager::getGames()
{
    return this->m_games;
}
