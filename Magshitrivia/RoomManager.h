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
	void deletePlayer(int id, LoggedUser user);
	void addPlayer(int id, LoggedUser user);
private:
	std::map<int, Room> m_rooms;
	static unsigned int currentRoomId;
};