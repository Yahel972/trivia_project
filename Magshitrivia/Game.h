#pragma once
#include "Question.h"
#include <map>
#include "LoggedUser.h"
#include "GameData.h"

class Game
{
public:
	Game() = default;
	Game(std::vector<Question> questions);
	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, std::string answer);
	void removePlayer(LoggedUser user);
	void addNewPlayer(LoggedUser user);

private:
	std::map<std::string, GameData> m_players;
	std::vector<Question> m_questions;
};