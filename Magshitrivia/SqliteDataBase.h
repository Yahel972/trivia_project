#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

class SqliteDataBase : public IDatabase
{
public:
	bool open() override; // for creating the database
	bool doesUserExist(std::string user) override;
	bool doesPasswordMatch(std::string username, std::string passwordToMatch) override;
	void addNewUser(std::string name, std::string password, std::string email) override;
	void insertQuestions() override;
	float getPlayerAverageAnswerTime(std::string username) override;
	int getNumOfCorrectAnswers(std::string username) override;
	int getNumOfTotalAnswers(std::string username) override;
	int getNumOfPlayerGames(std::string username) override;
private:
	sqlite3* db;
	static int callback_single_string(void* data, int argc, char** argv, char** azColName);
	static int callback_times(void* data, int argc, char** argv, char** azColName);
	static int callback_single_int(void* data, int argc, char** argv, char** azColName);
	std::string getQuestion(std::string question, std::string correctAnswer, std::string incorrectAnswer1, std::string incorrectAnswer2, std::string incorrectAnswer3);
};