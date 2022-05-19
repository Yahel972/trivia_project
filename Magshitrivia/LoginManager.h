#pragma once
#include "SqliteDataBase.h"
#include <vector>
#include "LoggedUser.h"

class LoginManager
{
public:
	LoginManager();
	bool signup(std::string username, std::string password, std::string email);
	bool login(std::string username, std::string password);
	void logout(std::string username);
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};