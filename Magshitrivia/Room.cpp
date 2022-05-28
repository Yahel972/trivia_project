#include "Room.h"

Room::Room(LoggedUser creator, RoomData data)
{
	this->m_metadata = data;
	this->m_users.push_back(creator);
}

void Room::addUser(LoggedUser userToAdd)
{
	this->m_users.push_back(userToAdd);
}

void Room::removeUser(LoggedUser userToRemove)
{
	for (int i = 0; i < this->m_users.size(); i++)
	{
		if (this->m_users[i].getUsername() == userToRemove.getUsername())
		{
			this->m_users.erase(this->m_users.begin() + i);
		}
	}
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> usernamesInRoom;
	for (auto user: this->m_users) {
		usernamesInRoom.push_back(user.getUsername());
	}
	return usernamesInRoom;
}

RoomData Room::getData()
{
	return this->m_metadata;
}
