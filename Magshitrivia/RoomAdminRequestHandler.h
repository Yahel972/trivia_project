#pragma once
#include "Room.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(Room* room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
private:
	RequestResult closeRoom(RequestInfo request);
	RequestResult startGame(RequestInfo request);
	RequestResult getRoomState(RequestInfo request);
	RequestResult getRooms(RequestInfo request);
	Room* m_room; // the address of the room the user is in (the admin)
	LoggedUser m_user; // the logged user (the admin of the room)
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};