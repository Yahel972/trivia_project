#pragma once
#include <iostream>
#include <vector>


class Question
{
public:
	Question() = default;
	Question(std::string question, std::vector<std::string> possibleAnswers);
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	std::string getCorrectAnswer();
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};