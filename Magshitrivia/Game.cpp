#include "Game.h"

Game::Game(IDatabase* datebase, int id, std::vector<Question> questions, int timeToAnswer)
{
	this->m_players = new std::map<std::string, GameData>;
	this->m_timeToAnswer = timeToAnswer;
	this->m_datebase = datebase;
	this->m_id = id;
	this->m_questions = questions;
}

Question Game::getQuestionForUser(LoggedUser user)
{
	Question question = this->m_questions[0];
	(*this->m_players)[user.getUsername()].setCurrentQuestion(question);
	this->m_questions.erase(this->m_questions.begin());
	return question;
}

void Game::submitAnswer(LoggedUser user, std::string answer, int answerdTime)
{
	int isCorrect = 0;
	if (answer == (*this->m_players)[user.getUsername()].getCurrentQuestion().getCorrectAnswer())
	{
		isCorrect = 1;
	}
	this->m_datebase->insertNewStatistic(this->m_id, 
		(*this->m_players)[user.getUsername()].getCurrentQuestion().getId(),
		user.getUsername(),
		isCorrect,
		answerdTime,
		this->m_timeToAnswer);
	if (isCorrect)
	{
		(*this->m_players)[user.getUsername()].setCorrectAnswerCount((*this->m_players)[user.getUsername()].getCorrectAnswerCount() + 1);
	}
	else
	{
		(*this->m_players)[user.getUsername()].setWrongAnswerCount((*this->m_players)[user.getUsername()].getWrongAnswerCount() + 1);
	}
	(*this->m_players)[user.getUsername()].setAverageAnswerTime((*this->m_players)[user.getUsername()].getAverageAnswerTime() + answerdTime);
}

void Game::removePlayer(LoggedUser user)
{
	return;
	//this->m_players.erase(user);
}

void Game::addNewPlayer(LoggedUser user)
{
	(*this->m_players)[user.getUsername()] = GameData();
}

std::string Game::getRightAnswer(std::string username)
{
	return (*this->m_players)[username].getCurrentQuestion().getCorrectAnswer();
}

std::map<std::string, GameData>* Game::getPlayers()
{
	return this->m_players;
}

void Game::setPlayers(std::map<std::string, GameData>* newPlayers)
{
	this->m_players = newPlayers;
}
