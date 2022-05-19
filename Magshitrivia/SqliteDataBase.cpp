#include "SqliteDataBase.h"
#include <io.h>
#include <string>


bool SqliteDataBase::open()
{
	std::string dbFileName = "galleryDB.sqlite";
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
		sqlStatement = "CREATE TABLE QUESTIONS ( \
			QUESTION TEXT NOT NULL, \
			CORRECT_ANSWER TEXT NOT NULL, \
			INCORRECT_ANSWER_1 TEXT NOT NULL, \
			INCORRECT_ANSWER_2 TEXT NOT NULL, \
			INCORRECT_ANSWER_3 TEXT NOT NULL);";
		res = sqlite3_exec(this->db, sqlStatement, nullptr, nullptr, errorMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "ERROR: QUESTIONS wasn't created" << std::endl;
			return false;
		}
		this->insertQuestions();
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

int SqliteDataBase::callback_single_string(void* data, int argc, char** argv, char** azColName)
{
	std::string* user = static_cast<std::string*>(data);
	*user = (std::string)((argv[0]));
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
