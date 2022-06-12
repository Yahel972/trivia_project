#include "MenuRequestHandler.h"

// constructor
MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory):m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory) 
{
	this->m_user = user;
}

// function checks if a given request is relevant (in this state- only create room or get rooms or get players in room or join room or get high scores or get user statistics or logout)
bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == CREATE_ROOM || request.id == GET_ROOMS || request.id == GET_PLAYERS_IN_ROOM || request.id == JOIN_ROOM || request.id == GET_HIGH_SCORES || request.id == GET_USER_STATISTICS || request.id == LOGOUT_CODE);
}

// function handles a request by its given code
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

// function signs out user 
RequestResult MenuRequestHandler::signout(RequestInfo request) 	
{
	RequestResult result;
	this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername());
	LogoutResponse response = { OK };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createLoginRequest();
	return result;
}

// function gets rooms
RequestResult MenuRequestHandler::getRooms(RequestInfo request)
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

// function gets players in room
RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo request) 
{

	GetPlayersInRoomRequest getPlayersRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(request.buffer);
	RequestResult result;
	std::vector<std::string> playersInRoom = this->m_roomManager.getAllRooms()[getPlayersRequest.roomId]->getAllUsers();
	GetPlayersInRoomResponse response;
	response.status = OK;
	response.players = playersInRoom;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}

// function gets personal stats
RequestResult MenuRequestHandler::getPersonalStats(RequestInfo request) 
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

// function gets high scores
RequestResult MenuRequestHandler::getHighScore(RequestInfo request) 
{
	RequestResult result;
	std::vector<std::string> stats = this->m_statisticsManager.getHighScore();
	getHighScoreResponse response;
	response.statistics = stats;
	response.status = OK;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = nullptr;
	return result;
}

// function enters a user into an existing room
RequestResult MenuRequestHandler::joinRoom(RequestInfo request) 
{
	JoinRoomRequest joinRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(request.buffer);
	this->m_roomManager.addPlayer(joinRequest.roomId, this->m_user);
	RequestResult result;
	JoinRoomResponse response = { OK };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user.getUsername());
	return result;
}

// function creates a new room
RequestResult MenuRequestHandler::createRoom(RequestInfo request) 
{
	CreateRoomRequest createRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(request.buffer);
	RoomData data;
	data.id = 0;
	data.isActive = false;
	data.maxPlayers = createRequest.maxUsers;
	data.name = createRequest.roomName;
	data.numOfQuestions = createRequest.questionCount;
	data.timePerQuestion = createRequest.answerTimeout;
	this->m_roomManager.createRoom(this->m_user.getUsername(), data);
	RequestResult result;
	CreateRoomResponse response = { OK };
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user.getUsername());
	return result;
}
