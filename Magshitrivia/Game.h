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
	void removePlayer(LoggedUser user);
	void addNewPlayer(LoggedUser user);
	std::string getRightAnswer(std::string username);
	std::map<std::string, GameData>* getPlayers();
	void setPlayers(std::map<std::string, GameData>* newPlayers);
private:
	IDatabase* m_datebase;
	int m_id;
	int m_timeToAnswer;
	std::map<std::string, GameData>* m_players;
	std::vector<Question> m_questions;
};