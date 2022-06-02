#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "RoomUserHandler.h"

class RequestHandlerFactory;
class RoomMemberRequestHandler : public RoomUserHandler
{
public:
	RoomMemberRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
private:
	RequestResult leaveRoom(RequestInfo request);
};
