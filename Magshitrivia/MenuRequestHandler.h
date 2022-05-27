#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"
#include "StatisticsManager.h"
#include "RoomManager.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
private:
	RequestResult signout(RequestInfo request);
	RequestResult getRooms(RequestInfo request);
	RequestResult getPlayersInRoom(RequestInfo request);
	RequestResult getPersonalStats(RequestInfo request);
	RequestResult getHighScore(RequestInfo request);
	RequestResult joinRoom(RequestInfo request);
	RequestResult createRoom(RequestInfo request);
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;
};
