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
	Room() = default;
	Room(LoggedUser creator, RoomData data);
	void addUser(LoggedUser userToAdd);
	void removeUser(LoggedUser userToRemove);
	std::vector<std::string> getAllUsers();
	RoomData getData();
	void start();
	void setUsers(std::vector<LoggedUser> newUsers);
private:
	RoomData m_metadata; // the room data
	std::vector<LoggedUser> m_users; // the users connected to the room
};