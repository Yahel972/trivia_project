#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room* room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
	this->m_room = room;
	this->m_user = user;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == LEAVE_ROOM || request.id == GET_ROOM_STATE || request.id == START_GAME);
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
	case START_GAME:
		return this->joinStartedGame(request);
		break;
	}
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo request)
{
	RequestResult requestResult;
	this->m_roomManager.deletePlayer(this->m_room->getData().id,this->m_user);
	requestResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername());
	LeaveRoomResponse response = { OK };
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo request)
{
	RequestResult requestResult;
	requestResult.newHandler = nullptr;
	GetRoomStateResponse response;
	response.answerTimeout = this->m_room->getData().timePerQuestion;
	response.hasGameBegun = this->m_room->getData().isActive;
	response.players = this->m_room->getAllUsers();
	response.questionCount = this->m_room->getData().numOfQuestions;
	response.status = OK;
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
}

RequestResult RoomMemberRequestHandler::joinStartedGame(RequestInfo request)
{
	RequestResult requestResult;
	requestResult.newHandler = this->m_handlerFactory.createJoinGameRequestHandler(this->m_user); // IMPORTANT: the handler should be to "GameRequestHandler"
	StartGameResponse response = { OK };
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
}
