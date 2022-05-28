#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
	this->m_room = room;
	this->m_user = user;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == LEAVE_ROOM || request.id == GET_ROOM_STATE);
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo request)
{
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo request)
{
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo request)
{
	return RequestResult();
}
