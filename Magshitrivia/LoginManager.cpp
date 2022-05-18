#include "LoginManager.h"

LoginManager::LoginManager()
{
	this->m_database = new SqliteDataBase();
	this->m_database->open();
}

void LoginManager::signup(std::string username, std::string password, std::string email)
{
	this->m_database->addNewUser(username, password, email);
}

void LoginManager::login(std::string username, std::string password)
{
	if (this->m_database->doesUserExist(username))
	{
		if (this->m_database->doesPasswordMatch(username, password))
		{
			LoggedUser user(username);
			this->m_loggedUsers.push_back(user);
		}
		else
		{
			std::cout << "password incorrect" << std::endl;
		}
	}
	else
	{
		std::cout << "user doesn't exist" << std::endl;
	}
}

void LoginManager::logout(std::string username)
{
	int index = 0;
	for (int i = 0; i < this->m_loggedUsers.size(); i++)
	{
		if (this->m_loggedUsers[i].getUsername() == username)
		{
			index = i;
		}
	}
	this->m_loggedUsers.erase(this->m_loggedUsers.begin() + index);
}
