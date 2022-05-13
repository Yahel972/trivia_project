#include "SqliteDataBase.h"

bool SqliteDataBase::open()
{
	return false;
}

bool SqliteDataBase::doesUserExist(std::string user)
{
	return false;
}

bool SqliteDataBase::doesPasswordMatch(std::string enterdPassword, std::string passwordToMatch)
{
	return false;
}

void SqliteDataBase::addNewUser(std::string name, std::string password, std::string email)
{
}
