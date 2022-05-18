#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler();
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
	RequestResult login(RequestInfo request);
	RequestResult signup(RequestInfo request);
private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};
