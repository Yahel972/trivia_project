#include "Game.h"

// constructor
Game::Game(IDatabase* datebase, int id, std::vector<Question> questions, int timeToAnswer)
{
	this->m_players = new std::map<std::string, GameData>;
	this->m_timeToAnswer = timeToAnswer;
	this->m_datebase = datebase;
	this->m_id = id;
	this->m_questions = questions;
}

/*
	Function gets the next question for a user
	Input: the user
	Output: the question
*/
Question Game::getQuestionForUser(LoggedUser user)
{
	Question question = this->m_questions[0];
	(*this->m_players)[user.getUsername()].setCurrentQuestion(question);
	this->m_questions.erase(this->m_questions.begin());
	return question;
}

/*
	Function submits answer of a user (adds statistic to database and the matching gamedata)
	Input: the user, his answer, the time it took him to answer the question
	Output: none
*/
void Game::submitAnswer(LoggedUser user, std::string answer, int answerdTime)
{
	
	// checking if the answer of the user is correct
	int isCorrect = 0;
	if (answer == (*this->m_players)[user.getUsername()].getCurrentQuestion().getCorrectAnswer()) 
	{
		isCorrect = 1;
	}

	// inserting new statistics to the matching table
	this->m_datebase->insertNewStatistic(this->m_id, 
		(*this->m_players)[user.getUsername()].getCurrentQuestion().getId(),
		user.getUsername(),
		isCorrect,
		answerdTime,
		this->m_timeToAnswer);


	// updating the game data of the current user
	if (isCorrect)
	{
		// increasing the number of correct answers by one
		(*this->m_players)[user.getUsername()].setCorrectAnswerCount((*this->m_players)[user.getUsername()].getCorrectAnswerCount() + 1);
	}
	else
	{
		// increasing the number of correct answers by one
		(*this->m_players)[user.getUsername()].setWrongAnswerCount((*this->m_players)[user.getUsername()].getWrongAnswerCount() + 1);
	}
	(*this->m_players)[user.getUsername()].setAverageAnswerTime((*this->m_players)[user.getUsername()].getAverageAnswerTime() + answerdTime); // summing the time it took the user to answer, will divide by the number of question when getting the final game results
}

/*
	Function adds a new player to existing game
	Input: the player
	Output: none
*/
void Game::addNewPlayer(LoggedUser user)
{
	(*this->m_players)[user.getUsername()] = GameData();
}

// right answer getter
std::string Game::getRightAnswer(std::string username)
{
	return (*this->m_players)[username].getCurrentQuestion().getCorrectAnswer();
}

// players getter
std::map<std::string, GameData>* Game::getPlayers()
{
	return this->m_players;
}

// players setter
void Game::setPlayers(std::map<std::string, GameData>* newPlayers)
{
	this->m_players = newPlayers;
}
