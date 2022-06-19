#pragma once
#include "Question.h"
#include <map>
#include "LoggedUser.h"
#include "GameData.h"
#include "IDatabase.h"


class Game
{
public:
	Game() = default;
	Game(IDatabase* datebase, int id, std::vector<Question> questions, int timeToAnswer);
	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, std::string answer, int answerdTime);
	void addNewPlayer(LoggedUser user);
	std::string getRightAnswer(std::string username);
	std::map<std::string, GameData>* getPlayers();
	void setPlayers(std::map<std::string, GameData>* newPlayers);
private:
	IDatabase* m_datebase; // the address of the main database file of the program
	int m_id; // the id of the room
	int m_timeToAnswer; // the time to answer every question in the game (the question time)
	std::map<std::string, GameData>* m_players; // a map that keeps usernames as key and the data for the current game as value
	std::vector<Question> m_questions; // the questions in the game
};