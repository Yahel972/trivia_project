#include "Room.h"
#include <string>

// constructor
Room::Room(LoggedUser creator, RoomData data)
{
	this->m_metadata = data;
	this->m_users.push_back(creator);
}

// function add user to room
void Room::addUser(LoggedUser userToAdd)
{
	this->m_users.push_back(userToAdd);
}

// function removes user from room
void Room::removeUser(LoggedUser userToRemove)
{
	for (int i = 0; i < this->m_users.size(); i++)
	{
		if (this->m_users[i].getUsername() == userToRemove.getUsername())
		{
			this->m_users.erase(this->m_users.begin() + i);
			break;
		}
	}
}

// getter for the usernames of the in the room (LoggedPlayer vector to string vector)
std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> usernamesInRoom;
	for (auto user: this->m_users) {
		usernamesInRoom.push_back(user.getUsername());
	}
	return usernamesInRoom;
}

// room data getter
RoomData Room::getData()
{
	return this->m_metadata;
}

// function changes the active status of the room to "true"
void Room::start()
{
	RoomData oldData = this->m_metadata;
	RoomData newData = {oldData.id, oldData.name, oldData.maxPlayers, oldData.numOfQuestions, oldData.timePerQuestion, true};
	this->m_metadata = newData;
}

// users setter
void Room::setUsers(std::vector<LoggedUser> newUsers)
{
	this->m_users = newUsers;
}
