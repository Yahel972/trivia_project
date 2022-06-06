#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(Game game ,LoggedUser user, GameManager& statisticsManager, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
private:
};