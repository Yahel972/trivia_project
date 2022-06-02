#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : RoomUserHandler(room, user, roomManager, handlerFactory)
{

}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == LEAVE_ROOM || request.id == GET_ROOM_STATE);
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo request)
{
	switch (request.id)
	{
	case LEAVE_ROOM:
		return this->leaveRoom(request);
		break;
	case GET_ROOM_STATE:
		return this->getRoomState(request);
		break;
	}
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo request)
{
	RequestResult requestResult;
	this->m_roomManager.deletePlayer(this->m_room.getData().id,this->m_user);
	requestResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername());
	LeaveRoomResponse response = { OK };
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
}
