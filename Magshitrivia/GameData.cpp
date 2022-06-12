#include "GameData.h"

// constructor
GameData::GameData(Question currentQuestion, unsigned int correctAnswerCount, unsigned int wrongAnswerCount, unsigned int averageAnswerTime)
{
	this->currentQuestion = currentQuestion;
	this->correctAnswerCount = correctAnswerCount;
	this->wrongAnswerCount = wrongAnswerCount;
	this->averageAnswerTime = averageAnswerTime;
}

// current question getter
Question GameData::getCurrentQuestion()
{
	return this->currentQuestion;
}

// correct answer count getter
unsigned int GameData::getCorrectAnswerCount()
{
	return this->correctAnswerCount;
}

// wrong answer count getter
unsigned int GameData::getWrongAnswerCount()
{
	return this->wrongAnswerCount;
}

// average answer time getter
unsigned int GameData::getAverageAnswerTime()
{
	return this->averageAnswerTime;
}

// current question setter
void GameData::setCurrentQuestion(Question newQuestion)
{
	this->currentQuestion = newQuestion;
}

// correct answer count setter
void GameData::setCorrectAnswerCount(unsigned int newCorrectAnswerCount)
{
	this->correctAnswerCount = newCorrectAnswerCount;
}

// wrong answer count setter 
void GameData::setWrongAnswerCount(unsigned int newWrongAnswerCount)
{
	this->wrongAnswerCount = newWrongAnswerCount;
}

// average answer time setter
void GameData::setAverageAnswerTime(unsigned int newAverageAnswerTime)
{
	this->averageAnswerTime = newAverageAnswerTime;
}
