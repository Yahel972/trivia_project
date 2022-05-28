#pragma once
#include <iostream>
#include <map>
#include "Room.h"

class RoomManager
{
public:
	RoomManager();
	void createRoom(LoggedUser creator, RoomData data);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRoomsData();
	std::map<int, Room> getAllRooms();
private:
	std::map<int, Room> m_rooms;
	static unsigned int currentRoomId;
};