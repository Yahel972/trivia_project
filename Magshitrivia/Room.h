#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"

typedef struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestions;
	unsigned int timePerQuestion;
	unsigned int isActive;
} RoomData;

class Room
{
public:
	void addUser(LoggedUser userToAdd);
	void removeUser(LoggedUser userToRemove);
	std::vector<std::string> getAllUsers();
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};