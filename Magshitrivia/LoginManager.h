#pragma once
#include "SqliteDataBase.h"
#include <vector>
#include "LoggedUser.h"
class LoginManager
{
public:
	
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};