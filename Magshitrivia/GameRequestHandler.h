#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(LoggedUser user, GameManager& gameManager, RequestHandlerFactory& handlerFactory);
	GameRequestHandler(Room room,LoggedUser user, GameManager& gameManager, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
	std::vector<PlayerResults> getPlayerResult();

private:
	Game m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult getGameResults(RequestInfo request);
	RequestResult getQuestion(RequestInfo request);
	RequestResult submitAnswer(RequestInfo request);
	RequestResult leaveGame(RequestInfo request);
};