#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"


class RoomUserHandler : public IRequestHandler
{
	public:
		RoomUserHandler(Room room, LoggedUser user, RoomManager & roomManager, RequestHandlerFactory & handlerFactory);
		virtual bool isRequestRelevant(RequestInfo request) = 0;
		virtual RequestResult handleRequest(RequestInfo request) = 0;
	protected:
		RequestResult getRoomState(RequestInfo request);
		Room m_room;
		LoggedUser m_user;
		RoomManager& m_roomManager;
		RequestHandlerFactory& m_handlerFactory;
};