#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(LoggedUser user, GameManager& gameManager, RequestHandlerFactory& handlerFactory) :m_gameManager(gameManager), m_handlerFactory(handlerFactory)
{
	this->m_user = user;
	std::vector<Game> games = this->m_gameManager.getGames();
	for (int i = 0; i < games.size(); i++)
	{
		std::map<std::string, GameData>* players = games[i].getPlayers();
		for (auto it = (*players).begin(); it != (*players).end(); it++)
		{
			if (it->first == user.getUsername())
			{
				this->m_game = games[i];
				this->m_game.setPlayers(players);
			}
		}
	}
}


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

std::vector<PlayerResults> GameRequestHandler::getPlayerResult()
{
	std::vector<PlayerResults> playerResults;
	std::map<std::string, GameData>* players = this->m_game.getPlayers();
	for (auto it = players->begin(); it != players->end(); it++)
	{
		PlayerResults result;
		result.username = it->first;
		result.averageAnswerTime = it->second.getAverageAnswerTime() / (it->second.getWrongAnswerCount() + it->second.getCorrectAnswerCount());
		result.correctAnswerCount = it->second.getCorrectAnswerCount();
		result.wrongAnswerCount = it->second.getWrongAnswerCount();
		playerResults.push_back(result);
	}
	return playerResults;
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
	RequestResult requestResult;
	requestResult.newHandler = nullptr;
	SubmitAnswerRequest submitAnswerRequest = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(request.buffer);
	SubmitAnswerResponse response;
	std::string correctAnswer = this->m_game.getRightAnswer(this->m_user.getUsername());
	this->m_game.submitAnswer(this->m_user, submitAnswerRequest.answer, submitAnswerRequest.timeToAnswer);
	response.status = OK;
	response.rightAnswer = correctAnswer;
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo request)
{
	RequestResult requestResult;
	requestResult.newHandler = nullptr;
	GetGameResultsResponse response;
	response.status = OK;
	response.results = this->getPlayerResult();
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(response);
	return requestResult;
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
