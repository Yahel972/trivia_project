#include "GameManager.h"

GameManager::GameManager(IDatabase* datebase)
{
    this->m_datebase = datebase;
}
Game GameManager::createGame(Room room)
{
    int numOfQuestion = room.getData().numOfQuestions;
    Game game(this->m_datebase->getQuestions(numOfQuestion));
    std::vector<std::string> users = room.getAllUsers();
    for (int i = 0; i < users.size(); i++)
    {
        game.addNewPlayer(LoggedUser(users[i]));
    }
    this->m_games.push_back(game);
    return game;
}
