#pragma once
#include "LoginManager.h"
#include "SqliteDataBase.h"
#include "LoginRequestHandler.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequest();
	LoginManager& getLoginManager();
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};