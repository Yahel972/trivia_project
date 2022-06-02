#pragma once
#include "Room.h"
#include "RoomManager.h"
#include "RoomUserHandler.h"
#include "RequestHandlerFactory.h"

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
