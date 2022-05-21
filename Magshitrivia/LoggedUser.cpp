#include "LoggedUser.h"

LoggedUser::LoggedUser()
{
	this->m_username = "";
}

LoggedUser::LoggedUser(std::string username)
{
	this->m_username = username;
}

std::string LoggedUser::getUsername()
{
	return this->m_username;
}
