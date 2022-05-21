#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory):m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory)
{
	this->m_user = user;
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == CREATE_ROOM || request.id == GET_ROOMS || request.id == GET_PLAYERS_IN_ROOM || request.id == JOIN_ROOM || request.id == GET_HIGH_SCORES || request.id == GET_USER_STATISTICS || request.id == LOGOUT_CODE);
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo request)
{
	return RequestResult();
}
