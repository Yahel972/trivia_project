#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory()
{
	this->m_loginManager = LoginManager();
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

