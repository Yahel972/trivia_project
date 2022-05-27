#pragma once
#include "LoginManager.h"
#include "SqliteDataBase.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

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
private:
	IDatabase* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
};