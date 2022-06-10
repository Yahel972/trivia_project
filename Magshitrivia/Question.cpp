#include "Question.h"

Question::Question(std::string question, std::vector<std::string> possibleAnswers)
{
	this->m_question = question;
	this->m_possibleAnswers = possibleAnswers;
}

std::string Question::getQuestion()
{
	return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
	return this->m_possibleAnswers;
}

std::string Question::getCorrectAnswer()
{
	return this->m_possibleAnswers[0];
}
