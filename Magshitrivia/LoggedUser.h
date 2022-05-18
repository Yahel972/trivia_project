#pragma once
#include <iostream>

class LoggedUser
{
public:
	std::string getUsername();
private:
	std::string m_username;
};