#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory()
{
	this->m_loginManager = LoginManager();
	this->m_database = this->m_loginManager.getDataBase();
	this->m_roomManager = RoomManager();
	this->m_StatisticsManager = StatisticsManager(this->m_database);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequest()
{
	LoginRequestHandler* loginRequest = new LoginRequestHandler((this->getLoginManager()), *this);
	return loginRequest;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(std::string username)
{
	LoggedUser user(username);
	MenuRequestHandler* menuRequest = new MenuRequestHandler(user, this->getRoomManager(), this->getStatisticsManager(), *this);
	return menuRequest;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(std::string username)
{
	LoggedUser user(username);	
	Room room;
	std::map<int, Room> allRooms = this->m_roomManager.getAllRooms();
	for (auto it = allRooms.begin(); it != allRooms.end(); it++)
	{
		std::vector<std::string> playersInRoom = it->second.getAllUsers();
		for (int i = 0; i < playersInRoom.size(); i++)
		{
			if (playersInRoom[i] == username)
			{
				room = it->second;
			}
		}
	}

	RoomAdminRequestHandler* roomAdminRequest = new RoomAdminRequestHandler(room, user, this->getRoomManager(), *this);
	return roomAdminRequest;
}

