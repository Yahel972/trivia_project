#include "GameData.h"

GameData::GameData(Question currentQuestion, unsigned int correctAnswerCount, unsigned int wrongAnswerCount, unsigned int averageAnswerTime)
{
	this->currentQuestion = currentQuestion;
	this->correctAnswerCount = correctAnswerCount;
	this->wrongAnswerCount = wrongAnswerCount;
	this->averageAnswerTime = averageAnswerTime;
}

Question GameData::getCurrentQuestion()
{
	return this->currentQuestion;
}

unsigned int GameData::getCorrectAnswerCount()
{
	return this->correctAnswerCount;
}

unsigned int GameData::getWrongAnswerCount()
{
	return this->wrongAnswerCount;
}

unsigned int GameData::getAverageAnswerTime()
{
	return this->averageAnswerTime;
}

void GameData::setCurrentQuestion(Question newQuestion)
{
	this->currentQuestion = newQuestion;
}

void GameData::setCorrectAnswerCount(unsigned int newCorrectAnswerCount)
{
	this->correctAnswerCount = newCorrectAnswerCount;
}

void GameData::setWrongAnswerCount(unsigned int newWrongAnswerCount)
{
	this->wrongAnswerCount = newWrongAnswerCount;
}

void GameData::setAverageAnswerTime(unsigned int newAverageAnswerTime)
{
	this->averageAnswerTime = newAverageAnswerTime;
}
