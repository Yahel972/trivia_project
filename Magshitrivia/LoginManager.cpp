#include "LoginManager.h"

LoginManager::LoginManager()
{
	this->m_database = new SqliteDataBase(); // allocatin the memory for the main database of the program
	this->m_database->open(); // opening the main database of the program
}

/*
	Function signs up user to the server
	Input: the name of the user to signup, his password, his mail
	Output: true if the user signed up sucecfully, false if not
*/
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

/*
	Function logs in a user to the server
	Input: the name of the user, the password of the user
	Output: 1 if the user logged succesfully, 2 if the user doesn't exist, 3 if the enterd password doesn't match the password in the database, 4 if the user is already connected
*/
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

/*
	Function logs out a user from the server
	Input: the name of the user to log out
	Output: none
*/
void LoginManager::logout(std::string username)
{
	for (int i = 0; i < this->m_loggedUsers.size(); i++) // going through every connected user
	{
		if (this->m_loggedUsers[i].getUsername() == username) // if user was found
		{
			this->m_loggedUsers.erase(this->m_loggedUsers.begin() + i);
		}
	}
}

// database getter
IDatabase* LoginManager::getDataBase()
{
	return this->m_database;
}
