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
	return (this->login(username, password));
}

int LoginManager::login(std::string username, std::string password)
{
	for (auto connectedUser: this->m_loggedUsers) {
		if (connectedUser.getUsername() == username)
		{
			std::cout << "already connected!" << std::endl;
			return USER_ALREADY_CONNCETED;
		}
	}
	if (this->m_database->doesUserExist(username))
	{
		if (this->m_database->doesPasswordMatch(username, password))
		{
			LoggedUser user(username);
			this->m_loggedUsers.push_back(user);
			return OK;
		}
		else
		{
			std::cout << "password incorrect" << std::endl;
			return PASSWORD_DOESNT_MATCH;
		}
	}
	else
	{
		std::cout << "user doesn't exist" << std::endl;
		return USER_DOESNT_EXISTS;
	}
}

void LoginManager::logout(std::string username)
{
	for (int i = 0; i < this->m_loggedUsers.size(); i++)
	{
		if (this->m_loggedUsers[i].getUsername() == username)
		{
			this->m_loggedUsers.erase(this->m_loggedUsers.begin() + i);
		}
	}
}

IDatabase* LoginManager::getDataBase()
{
	return this->m_database;
}
