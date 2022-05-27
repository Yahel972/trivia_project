#include "StatisticsManager.h"

StatisticsManager::StatisticsManager()
{
	this->m_database = nullptr;
}

StatisticsManager::StatisticsManager(IDatabase* database)
{
	this->m_database = database;
}

std::vector<std::string> StatisticsManager::getHighScore()
{
	std::vector<std::string> users = this->m_database->getUsers();
	std::vector<int> allScores;
	for (auto user : users) {
		allScores.push_back(this->getUserScore(user));
	}
	std::sort(allScores.begin(), allScores.end());
	std::vector<std::string> bestScores;
	for (int i = 0; i < 3 && i < allScores.size(); i++)
	{
		bestScores.push_back(std::to_string(allScores[i]));
	}
	return bestScores;
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	std::vector<std::string> statistics;
	statistics.push_back("Games played:" + std::to_string(this->m_database->getNumOfPlayerGames(username)));
	statistics.push_back("Total answers:" + std::to_string(this->m_database->getNumOfTotalAnswers(username)));
	statistics.push_back("Correct answers:" + std::to_string(this->m_database->getNumOfCorrectAnswers(username)));
	statistics.push_back("Average answer time:" + std::to_string(this->m_database->getPlayerAverageAnswerTime(username)));
	return statistics;
}

int StatisticsManager::getUserScore(std::string username)
{
	// formula: [(1 - (({response time} / {question timer}}) / 2)) * 1000]
	return ((1 - ((this->m_database->getPlayerAverageAnswerTime(username) / this->m_database->getPlayerAverageAnswerTime(username)) / 2)) * 1000);
}
