#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Room.h"
#include "LoggedUser.h"
#include "RoomUserHandler.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public RoomUserHandler
{
public:
	RoomAdminRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
private:
	RequestResult closeRoom(RequestInfo request);
	RequestResult startGame(RequestInfo request);
};
