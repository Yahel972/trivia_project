#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"


class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler();
	bool isRequestRelevant(RequestInfo request) const;
	RequestResult handleRequest(RequestInfo request) const;
	RequestResult login(RequestInfo request);
	RequestInfo signup(RequestInfo request);
private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};
