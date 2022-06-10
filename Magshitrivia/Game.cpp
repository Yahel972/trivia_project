#include "Game.h"

Game::Game(std::vector<Question> questions)
{
	this->m_questions = questions;
}

Question Game::getQuestionForUser(LoggedUser user)
{
	Question question = this->m_questions[0];
	this->m_players[user.getUsername()].setCurrentQuestion(question);
	this->m_questions.erase(this->m_questions.begin());
	return question;
}

void Game::submitAnswer(LoggedUser user, std::string answer)
{
	
}

void Game::removePlayer(LoggedUser user)
{
	return;
	//this->m_players.erase(user);
}

void Game::addNewPlayer(LoggedUser user)
{

}
