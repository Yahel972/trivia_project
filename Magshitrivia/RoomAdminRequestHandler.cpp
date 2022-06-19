#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room* room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
	this->m_room = room;
	this->m_user = user;
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == CLOSE_ROOM || request.id == START_GAME || request.id == GET_ROOM_STATE || request.id == GET_ROOMS);
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
	case GET_ROOMS:
		return this->getRooms(request);
		break;
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo request)
{
	RequestResult requestResult;
	requestResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername());
	CloseRoomResponse response = { OK };
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	this->m_roomManager.deleteRoom(this->m_room->getData().id);
	return requestResult;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo request)
{
	if (!this->m_room->getData().isActive)
	{
		this->m_room->start();
	}
	RequestResult requestResult;
	requestResult.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user); // IMPORTANT: the handler should be to "GameRequestHandler"
	StartGameResponse response = { OK };
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo request)
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

RequestResult RoomAdminRequestHandler::getRooms(RequestInfo request) // done
{
	RequestResult result;
	std::vector<RoomData> rooms = this->m_roomManager.getRoomsData();
	GetRoomsResponse response;
	response.rooms = rooms;
	response.status = OK;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}