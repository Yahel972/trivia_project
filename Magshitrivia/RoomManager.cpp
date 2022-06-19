#include "RoomManager.h"

RoomManager::RoomManager()
{

}

unsigned int RoomManager::currentRoomId = 1;

void RoomManager::createRoom(LoggedUser creator, RoomData data)
{
	data.id = currentRoomId;
	currentRoomId += 1;
	this->m_rooms[data.id] = new Room(creator, data);
}

void RoomManager::deleteRoom(int id)
{
	std::vector<std::string> users = this->m_rooms[id]->getAllUsers();
	for (int i = 0; i < users.size(); i++)
	{
		this->m_rooms[id]->removeUser(LoggedUser(users[i]));
	}
	this->m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	return (this->m_rooms[id]->getData().isActive);
}

std::vector<RoomData> RoomManager::getRoomsData()
{
	std::vector<RoomData> allRoomsData;
	for (std::map<int, Room*>::iterator it = this->m_rooms.begin(); it != this->m_rooms.end();)
	{
		if (this->m_rooms[it->first]->getAllUsers().size() == 0)
		{
			this->m_rooms.erase(it++->first);
		}
		else
		{
			allRoomsData.push_back(it->second->getData());
			++it;
		}
	}
	return allRoomsData;
}

std::map<int, Room*> RoomManager::getAllRooms()
{
	return this->m_rooms;
}

void RoomManager::deletePlayer(int id, LoggedUser user)
{
	if (this->m_rooms.find(id) != this->m_rooms.end())
	{
		this->m_rooms[id]->removeUser(user);
	}
}

void RoomManager::addPlayer(int id, LoggedUser user)
{
	this->m_rooms[id]->addUser(user);
}