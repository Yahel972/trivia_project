#include "RoomManager.h"

RoomManager::RoomManager()
{

}

unsigned int RoomManager::currentRoomId = 1;

void RoomManager::createRoom(LoggedUser creator, RoomData data)
{
	data.id = currentRoomId;
	currentRoomId += 1;
	Room newRoom(creator, data);
	this->m_rooms[data.id] = newRoom;
}

void RoomManager::deleteRoom(int id)
{
	this->m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	return (this->m_rooms[id].getData().isActive);
}

std::vector<RoomData> RoomManager::getRoomsData()
{
	std::vector<RoomData> allRoomsData;
	for (std::map<int, Room>::iterator it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
	{
		allRoomsData.push_back(it->second.getData());
	}
	return allRoomsData;
}

std::map<int, Room> RoomManager::getAllRooms()
{
	return this->m_rooms;
}
