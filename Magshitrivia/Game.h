#pragma once
#include "Question.h"
#include <map>
#include "LoggedUser.h"

typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
} GameData;

class Game
{
public:
	void getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, std::string answer);
	void removePlayer(LoggedUser user);
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
};