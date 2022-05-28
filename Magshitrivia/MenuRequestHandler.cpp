#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory):m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory) 
{
	this->m_user = user;
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == CREATE_ROOM || request.id == GET_ROOMS || request.id == GET_PLAYERS_IN_ROOM || request.id == JOIN_ROOM || request.id == GET_HIGH_SCORES || request.id == GET_USER_STATISTICS || request.id == LOGOUT_CODE);
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo request)
{
	switch (request.id)
	{
	case LOGOUT_CODE:
		return this->signout(request);
		break;
	case CREATE_ROOM:
		return this->createRoom(request);
	case JOIN_ROOM:
		return this->joinRoom(request);
	case GET_ROOMS:
		return this->getRooms(request);
	case GET_PLAYERS_IN_ROOM:
		return this->getPlayersInRoom(request);
		break;
	case GET_HIGH_SCORES:
		return this->getHighScore(request);
		break;
	case GET_USER_STATISTICS:
		return this->getPersonalStats(request);
		break;
	}
}

RequestResult MenuRequestHandler::signout(RequestInfo request) // done	
{
	RequestResult result;
	this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername());
	LogoutResponse response = { OK };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createLoginRequest();
	return result;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo request) // done
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

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo request) // done
{

	GetPlayersInRoomRequest getPlayersRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(request.buffer);
	RequestResult result;
	std::vector<std::string> playersInRoom = this->m_roomManager.getAllRooms()[getPlayersRequest.roomId].getAllUsers();
	GetPlayersInRoomResponse response;
	response.players = playersInRoom;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo request) // done
{
	RequestResult result;
	std::vector<std::string> stats = this->m_statisticsManager.getUserStatistics(this->m_user.getUsername());
	getPersonalStatsResponse response;
	response.statistics = stats;
	response.status = OK;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo request) // done
{
	RequestResult result;
	std::vector<std::string> stats = this->m_statisticsManager.getHighScore();
	getPersonalStatsResponse response;
	response.statistics = stats;
	response.status = OK;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo request) // done
{
	JoinRoomRequest joinRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(request.buffer);
	this->m_roomManager.getAllRooms()[joinRequest.roomId].addUser(this->m_user.getUsername());
	RequestResult result;
	JoinRoomResponse response = { OK };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo request) // done
{
	CreateRoomRequest createRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(request.buffer);
	RoomData data;
	data.id = 0;
	data.isActive = true;
	data.maxPlayers = createRequest.maxUsers;
	data.name = createRequest.roomName;
	data.numOfQuestions = createRequest.questionCount;
	data.timePerQuestion = createRequest.answerTimeout;
	this->m_roomManager.createRoom(this->m_user.getUsername(), data);
	RequestResult result;
	CreateRoomResponse response = { OK };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}
