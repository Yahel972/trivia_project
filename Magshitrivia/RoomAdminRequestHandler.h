#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Room.h"
#include "LoggedUser.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
private:
	RequestResult closeRoom(RequestInfo request);
	RequestResult startGame(RequestInfo request);
	RequestResult getRoomState(RequestInfo request);
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

};
