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
			EMAIL TEXT NOT NULL);";
		res = sqlite3_exec(this->db, sqlStatement, nullptr, nullptr, errorMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "ERROR: USERS wasn't created" << std::endl;
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

int SqliteDataBase::callback_single_string(void* data, int argc, char** argv, char** azColName)
{
	std::string* user = static_cast<std::string*>(data);
	*user = (std::string)((argv[0]));
	return 0;
}
