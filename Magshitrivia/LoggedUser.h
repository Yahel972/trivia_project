#pragma once
#include <iostream>

class LoggedUser
{
public:
	LoggedUser();
	LoggedUser(std::string username);
	std::string getUsername();
private:
	std::string m_username; // the username
};