#include "LoginManager.h"

LoginManager::LoginManager()
{
	this->m_database = new SqliteDataBase();
	this->m_database->open();
}

bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (this->m_database->doesUserExist(username))
	{
		std::cout << "user already exists!" << std::endl;
		return false;
	}
	this->m_database->addNewUser(username, password, email);
	return this->m_database->doesUserExist(username);
}

bool LoginManager::login(std::string username, std::string password)
{
	for (auto connectedUser: this->m_loggedUsers) {
		if (connectedUser.getUsername() == username)
		{
			std::cout << "already connected!" << std::endl;
			return false;
		}
	}
	if (this->m_database->doesUserExist(username))
	{
		if (this->m_database->doesPasswordMatch(username, password))
		{
			LoggedUser user(username);
			this->m_loggedUsers.push_back(user);
			return true;
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
	return false;
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
