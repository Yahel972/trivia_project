#include "Question.h"

// constructor
Question::Question(int id, std::string question, std::string correctAnswer, std::vector<std::string> possibleAnswers)
{
	this->correctAnswer = correctAnswer;
	this->id = id;
	this->m_question = question;
	this->m_possibleAnswers = possibleAnswers;
}

// question getter
std::string Question::getQuestion()
{
	return this->m_question;
}

// possible answers getter
std::vector<std::string> Question::getPossibleAnswers()
{
	return this->m_possibleAnswers;
}

// correct answer getter
std::string Question::getCorrectAnswer()
{
	return this->correctAnswer;
}

//  id getter
int Question::getId()
{
	return this->id;
}
