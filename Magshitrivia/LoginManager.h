#pragma once
#include "SqliteDataBase.h"
#include <vector>
#include "LoggedUser.h"

#define OK 1
#define USER_DOESNT_EXISTS 2
#define PASSWORD_DOESNT_MATCH 3
#define USER_ALREADY_CONNCETED 4

class LoginManager
{
public:
	LoginManager();
	bool signup(std::string username, std::string password, std::string email);
	int login(std::string username, std::string password);
	void logout(std::string username);
	IDatabase* getDataBase();
private:
	IDatabase* m_database; // the address of the main database file of the program
	std::vector<LoggedUser> m_loggedUsers; // vector of every user currently logged 
};