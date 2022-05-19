#pragma once
#include <iostream>
#include <map>
#include "Room.h"

class RoomManager
{
public:
	void createRoom(LoggedUser creator, RoomData data);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();
private:
	std::map<int, Room> m_rooms;
};