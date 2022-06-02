#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : RoomUserHandler(room, user, roomManager, handlerFactory)
{

}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == CLOSE_ROOM || request.id == START_GAME || request.id == GET_ROOM_STATE);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo request)
{
	switch (request.id)
	{
	case CLOSE_ROOM:
		return this->closeRoom(request);
		break;
	case START_GAME:
		return this->startGame(request);
	case GET_ROOM_STATE:
		return this->getRoomState(request);
		break;
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo request)
{
	RequestResult requestResult;
	requestResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername());
	CloseRoomResponse response = { OK };
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	this->m_roomManager.deleteRoom(this->m_room.getData().id);
	return requestResult;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo request)
{
	if (!this->m_room.getData().isActive)
	{
		this->m_room.start();
	}
	RequestResult requestResult;
	requestResult.newHandler = nullptr; // IMPORTANT: the handler should be to "GameRequestHandler"
	StartGameResponse response = { OK };
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
}
