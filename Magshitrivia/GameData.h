#pragma once
#include "Question.h"
class GameData
{
public:
	GameData() = default;
	GameData(Question currentQuestion, unsigned int correctAnswerCount, unsigned int wrongAnswerCount, unsigned int averageAnswerTime);
	Question getCurrentQuestion();
	unsigned int getCorrectAnswerCount();
	unsigned int getWrongAnswerCount();
	unsigned int getAverageAnswerTime();
	void setCurrentQuestion(Question newQuestion);
	void setCorrectAnswerCount(unsigned int newCorrectAnswerCount);
	void setWrongAnswerCount(unsigned int newWrongAnswerCount);
	void setAverageAnswerTime(unsigned int newAverageAnswerTime);
private:
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};