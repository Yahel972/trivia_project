#include "LoggedUser.h"

// default constructor
LoggedUser::LoggedUser()
{
	this->m_username = "";
}

// constructor
LoggedUser::LoggedUser(std::string username)
{
	this->m_username = username;
}

// username getter
std::string LoggedUser::getUsername()
{
	return this->m_username;
}
