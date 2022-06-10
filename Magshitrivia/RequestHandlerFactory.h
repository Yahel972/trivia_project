#pragma once
#include "LoginManager.h"
#include "SqliteDataBase.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomUserHandler.h"	
#include "GameRequestHandler.h"
#include "GameManager.h"



class GameRequestHandler;

class RoomMemberRequestHandler;

class RoomAdminRequestHandler;

class LoginRequestHandler;

class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	LoginRequestHandler* createLoginRequest();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler(std::string username);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
	RoomAdminRequestHandler* createRoomAdminRequestHandler(std::string username);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(std::string username);
	GameManager& getGameManager();
	GameRequestHandler* createGameRequestHandler(LoggedUser user);
private:
	IDatabase* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
	GameManager m_gameManager;
};