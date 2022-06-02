#include "RoomUserHandler.h"

RoomUserHandler::RoomUserHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
	this->m_room = room;
	this->m_user = user;
}

RequestResult RoomUserHandler::getRoomState(RequestInfo request)
{
	RequestResult requestResult;
	requestResult.newHandler = nullptr;
	GetRoomStateResponse response;
	response.answerTimeout = this->m_room.getData().timePerQuestion;
	response.hasGameBegun = this->m_room.getData().isActive;
	response.players = this->m_room.getAllUsers();
	response.questionCount = this->m_room.getData().numOfQuestions;
	response.status = OK;
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
}
