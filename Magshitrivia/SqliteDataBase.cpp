#include "SqliteDataBase.h"
#include <io.h>
#include <string>
#include <vector>


bool SqliteDataBase::open()
{
	std::string dbFileName = "triviaDB.sqlite";
	char** errorMessage = 0;
	int file_exist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &(this->db));
	if (res != SQLITE_OK) {
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	if (file_exist != 0) {

		// creating the users table
		const char* sqlStatement = "CREATE TABLE USERS ( \
			USERNAME TEXT NOT NULL, \
			PASSWORD TEXT NOT NULL, \
			EMAIL TEXT NOT NULL, \
			PRIMARY KEY(USERNAME));";
		res = sqlite3_exec(this->db, sqlStatement, nullptr, nullptr, errorMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "ERROR: USERS wasn't created" << std::endl;
			return false;
		}
		sqlStatement = "CREATE TABLE GAMES ( \
			GAME_ID INTEGER NOT NULL, \
			PRIMARY KEY(GAME_ID AUTOINCREMENT));";
		res = sqlite3_exec(this->db, sqlStatement, nullptr, nullptr, errorMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "ERROR: GAMES wasn't created" << std::endl;
			return false;
		}
		// creating the questions table
		sqlStatement = "CREATE TABLE QUESTIONS ( \
			QUESTION_ID INTEGER NOT NULL, \
			QUESTION TEXT NOT NULL, \
			CORRECT_ANSWER TEXT NOT NULL, \
			INCORRECT_ANSWER_1 TEXT NOT NULL, \
			INCORRECT_ANSWER_2 TEXT NOT NULL, \
			INCORRECT_ANSWER_3 TEXT NOT NULL, \
			PRIMARY KEY(QUESTION_ID AUTOINCREMENT));";
		res = sqlite3_exec(this->db, sqlStatement, nullptr, nullptr, errorMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "ERROR: QUESTIONS wasn't created" << std::endl;
			return false;
		}
		this->insertQuestions();
			sqlStatement = "CREATE TABLE STATISTICS ( \
			GAME_ID INTEGER NOT NULL, \
			QUESTION_ID INTEGER NOT NULL, \
			USERNAME TEXT NOT NULL, \
			IS_CORRECT INTEGER NOT NULL, \
			TIME_TO_ANSWER INTEGER NOT NULL, \
			TIME_FOR_QUESTION INTEGER NOT NULL, \
			FOREIGN KEY(GAME_ID) REFERENCES GAMES(GAME_ID), \
			FOREIGN KEY(QUESTION_ID) REFERENCES QUESTIONS(QUESTION_ID), \
			FOREIGN KEY(USERNAME) REFERENCES USERS(USERNAME));";
		res = sqlite3_exec(this->db, sqlStatement, nullptr, nullptr, errorMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "ERROR: STATISTICS wasn't created" << std::endl;
			return false;
		}
	}
	return true;
}

bool SqliteDataBase::doesUserExist(std::string user)
{
	char** errMessage = nullptr;
	std::string sqlStatement = "SELECT USERNAME FROM USERS where USERNAME='" + user + "';";
	std::string existingUser = "";
	sqlite3_exec(this->db, sqlStatement.c_str(), callback_single_string, &existingUser, errMessage);
	return (user == existingUser);
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string passwordToMatch)
{
	char** errMessage = nullptr;
	std::string sqlStatement = "SELECT PASSWORD FROM USERS where USERNAME='" + username + "';";
	std::string existingPassword = "";
	sqlite3_exec(this->db, sqlStatement.c_str(), callback_single_string, &existingPassword, errMessage);
	return (existingPassword == passwordToMatch);
}

void SqliteDataBase::addNewUser(std::string name, std::string password, std::string email)
{
	char** errMessage = nullptr;
	std::string sqlStatement = "INSERT INTO USERS(USERNAME,PASSWORD,EMAIL) VALUES('" + name + "','" + password + "','" + email + "');";
	sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, errMessage);
}

float SqliteDataBase::getPlayerAverageRightAnswerResponseTime(std::string username)
{
	float sum = 0;
	std::vector<int> times;
	char** errMessage = nullptr;
	std::string sqlStatement = "SELECT TIME_TO_ANSWER FROM STATISTICS where USERNAME='" + username + "' AND IS_CORRECT=1;";
	sqlite3_exec(this->db, sqlStatement.c_str(), callback_times, &times, errMessage);
	for (int i = 0; i < times.size(); i++)
	{
		sum += times[i];
	}
	return (sum / times.size());
}

float SqliteDataBase::getPlayerAverageRightAnswerTime(std::string username)
{
	float sum = 0;
	std::vector<int> times;
	char** errMessage = nullptr;
	std::string sqlStatement = "SELECT TIME_FOR_QUESTION FROM STATISTICS where USERNAME='" + username + "' AND IS_CORRECT=1;";
	sqlite3_exec(this->db, sqlStatement.c_str(), callback_times, &times, errMessage);
	for (int i = 0; i < times.size(); i++)
	{
		sum += times[i];
	}
	return (sum / times.size());
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string username)
{
	int numOfCorrectAnswers = 0;
	char** errMessage = nullptr;
	std::string sqlStatement = "SELECT COUNT() FROM STATISTICS where USERNAME='" + username + "' AND IS_CORRECT=1;";
	sqlite3_exec(this->db, sqlStatement.c_str(), callback_single_int, &numOfCorrectAnswers, errMessage);
	return numOfCorrectAnswers;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string username)
{
	int numOfCorrectAnswers = 0;
	char** errMessage = nullptr;
	std::string sqlStatement = "SELECT COUNT(QUESTION_ID) FROM STATISTICS where USERNAME='" + username + "';";
	sqlite3_exec(this->db, sqlStatement.c_str(), callback_single_int, &numOfCorrectAnswers, errMessage);
	return numOfCorrectAnswers;
}

int SqliteDataBase::getNumOfPlayerGames(std::string username)
{
	int numOfGames = 0;
	char** errMessage = nullptr;
	std::string sqlStatement = "SELECT COUNT(DISTINCT GAME_ID) FROM STATISTICS where USERNAME='" + username + "';";
	sqlite3_exec(this->db, sqlStatement.c_str(), callback_single_int, &numOfGames, errMessage);
	return numOfGames;
}

std::vector<std::string> SqliteDataBase::getUsers()
{
	std::vector<std::string> users;
	char** errMessage = nullptr;
	std::string sqlStatement = "SELECT USERNAME FROM USERS";
	sqlite3_exec(this->db, sqlStatement.c_str(), callback_users, &users, errMessage);
	return users;
}

int SqliteDataBase::callback_single_string(void* data, int argc, char** argv, char** azColName)
{
	std::string* user = static_cast<std::string*>(data);
	*user = (std::string)((argv[0]));
	return 0;
}

int SqliteDataBase::callback_times(void* data, int argc, char** argv, char** azColName)
{
	std::vector<int>* times = static_cast<std::vector<int>*>(data);
	for (int i = 0; i < argc; i++) {
		times->push_back(atoi(argv[i]));
	}
	return 0;
}

int SqliteDataBase::callback_single_int(void* data, int argc, char** argv, char** azColName)
{
	int* num = static_cast<int*>(data);
	*num = atoi(argv[0]);
	return 0;
}

int SqliteDataBase::callback_users(void* data, int argc, char** argv, char** azColName)
{
	std::vector<std::string>* users = static_cast<std::vector<std::string>*>(data);
	for (int i = 0; i < argc; i++) {
		users->push_back(argv[i]);
	}
	return 0;
}

void SqliteDataBase::insertQuestions()
{
	char** errMessage = nullptr;
	sqlite3_exec(this->db, getQuestion("What term is best associated with Sigmund Freud?", "Psychoanalysis", "Cognitive-Behavioral Therapy", "Theory of Gravity", "Dialectical Behavior Therapy").c_str(), nullptr, nullptr, errMessage);
	sqlite3_exec(this->db, getQuestion("Which American civilization is the source of the belief that the world would end or drastically change on December 21st, 2012?", "The Mayans", "The Incas", "The Aztecs", "The Navajos").c_str(), nullptr, nullptr, errMessage);
	sqlite3_exec(this->db, getQuestion("What is the exact length of one non - curved part in Lane 1 of an Olympic Track?", "84.39m", "100m", "100yd", "109.36yd").c_str(), nullptr, nullptr, errMessage);
	sqlite3_exec(this->db, getQuestion("Which of the following tabletop games is the oldest?", "Go", "Chess", "Mahjong", "Shogi").c_str(), nullptr, nullptr, errMessage);
	sqlite3_exec(this->db, getQuestion("What colour hair does the main character of the Yu-Gi-Oh! original anime series have?", "Red, black and yellow", "Red, yellow and green", "Red, black and green", "Red, purple and blue").c_str(), nullptr, nullptr, errMessage);
	sqlite3_exec(this->db, getQuestion("What was the name given to Android 4.3?", "Jelly Bean", "Lollipop", "Nutella", "Froyo").c_str(), nullptr, nullptr, errMessage);
	sqlite3_exec(this->db, getQuestion("In Greek Mythology, who killed Achilles?", "Paris", "Hector", "Helen", "Pericles").c_str(), nullptr, nullptr, errMessage);
	sqlite3_exec(this->db, getQuestion(".at is the top-level domain for what country?", "Austria", "Argentina", "Australia", "Angola").c_str(), nullptr, nullptr, errMessage);
	sqlite3_exec(this->db, getQuestion("What is the capital city of New Zealand?", "Wellington", "Auckland", "Christchurch", "Melbourne").c_str(), nullptr, nullptr, errMessage);
	sqlite3_exec(this->db, getQuestion("What year was hockey legend Wayne Gretzky born?", "1961", "1965", "1959", "1963").c_str(), nullptr, nullptr, errMessage);
}

std::string SqliteDataBase::getQuestion(std::string question, std::string correctAnswer, std::string incorrectAnswer1, std::string incorrectAnswer2, std::string incorrectAnswer3)
{
	std::string completeQuestion = "INSERT INTO QUESTIONS(QUESTION,CORRECT_ANSWER,INCORRECT_ANSWER_1,INCORRECT_ANSWER_2,INCORRECT_ANSWER_3) VALUES('" + question + "','" + correctAnswer + "','" + incorrectAnswer1 + "','" + incorrectAnswer2 + "','" + incorrectAnswer3 + "');";
	return completeQuestion;
}
