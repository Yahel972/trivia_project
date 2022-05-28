#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
private:
	RequestResult leaveRoom(RequestInfo request);
	RequestResult getRoomState(RequestInfo request);
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

};
