#pragma once
#include <iostream>
#include <vector>


class Question
{
public:
	Question() = default;
	Question(int id, std::string question, std::string correctAnswer, std::vector<std::string> possibleAnswers);
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	std::string getCorrectAnswer();
	int getId();
private:
	int id; // question id
	std::string m_question; // the question
	std::string correctAnswer; // the correct answer 
	std::vector<std::string> m_possibleAnswers; // all 4 possible answers 
};