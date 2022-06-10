#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(Room room, LoggedUser user, GameManager& gameManager, RequestHandlerFactory& handlerFactory) :m_gameManager(gameManager), m_handlerFactory(handlerFactory)
{
	this->m_game = this->m_gameManager.createGame(room);
	this->m_user = user;
}

bool GameRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == LEAVE_GAME || request.id == GET_QUESTION || request.id == SUBMIT_ANSWER || request.id == GET_GAME_RESULTS);
}

RequestResult GameRequestHandler::handleRequest(RequestInfo request)
{
	switch (request.id)
	{
	case LEAVE_GAME:
		return this->leaveGame(request);
		break;
	case GET_QUESTION:
		return this->getQuestion(request);
		break;
	case SUBMIT_ANSWER:
		return this->submitAnswer(request);
	case GET_GAME_RESULTS:
		return this->getGameResults(request);
		break;
	}
}

RequestResult GameRequestHandler::getQuestion(RequestInfo request)
{	
	RequestResult requestResult;
	requestResult.newHandler = nullptr;
	GetQuestionResponse response;
	response.status = OK;
	Question question = this->m_game.getQuestionForUser(this->m_user);
	response.question = question.getQuestion();
	response.answers = question.getPossibleAnswers();
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo request)
{
	return RequestResult();
}

RequestResult GameRequestHandler::getGameResults(RequestInfo request)
{
	return RequestResult();
}

RequestResult GameRequestHandler::leaveGame(RequestInfo request)
{
	RequestResult requestResult;
	int id = 0;
	std::map<int, Room*> allRooms = this->m_handlerFactory.getRoomManager().getAllRooms();
	for (auto it = allRooms.begin(); it != allRooms.end(); it++)
	{
		std::vector<std::string> users = it->second->getAllUsers();
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i] == this->m_user.getUsername())
			{
				id = it->first;
			}
		}
	}
	this->m_handlerFactory.getRoomManager().deletePlayer(id,this->m_user);
	requestResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername());
	LeaveGameResponse response = { OK };
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
}
