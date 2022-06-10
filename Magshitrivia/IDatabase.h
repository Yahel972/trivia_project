#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Question.h"


class IDatabase
{
public:
	virtual bool open() = 0; // for creating the database
	virtual bool doesUserExist(std::string user) = 0;
	virtual bool doesPasswordMatch(std::string enterdPassword, std::string passwordToMatch) = 0;
	virtual void addNewUser(std::string name, std::string password, std::string email) = 0;
	virtual void insertQuestions() = 0;
	virtual std::vector<int> getPlayerTimesToAnswer(std::string username) = 0;
	virtual std::vector<int> getPlayerTimesForQuestions(std::string username) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
	virtual std::vector<std::string> getUsers() = 0;
	virtual std::vector<Question> getQuestions(int numOfQuestions) = 0;
};