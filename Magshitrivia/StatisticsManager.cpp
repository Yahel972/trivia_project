#include "StatisticsManager.h"
#include <map>     
#include <utility>

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
	std::vector<std::pair<std::string, int>> allScores;
	std::map<std::string, int> usersScores;
	for (auto user : users) {
		usersScores[user] = this->getUserScore(user);
	}

	// copy key-value pairs from the map to the vector
	std::copy(usersScores.begin(),
		usersScores.end(),
		std::back_inserter<std::vector<std::pair<std::string, int>>>(allScores));

	// sort the vector by increasing the order of its pair's second value
	// if the second value is equal, order by the pair's first value
	std::sort(allScores.begin(), allScores.end(),
		[](const std::pair<std::string, int>& l, const std::pair<std::string, int>& r)
		{
			if (l.second != r.second) {
				return l.second < r.second;
			}

			return l.first < r.first;
		});
	std::sort(allScores.begin(), allScores.end());
	std::vector<std::string> bestScores;
	for (int i = 0; i < 3 && i < allScores.size(); i++)
	{
		bestScores.push_back(allScores[i].first + ":" + std::to_string(allScores[i].second));
	}
	return bestScores;
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	std::vector<std::string> statistics;
	statistics.push_back(std::to_string(this->m_database->getNumOfPlayerGames(username))); // games played
	statistics.push_back(std::to_string(this->m_database->getNumOfTotalAnswers(username))); // total answers
	statistics.push_back(std::to_string(this->m_database->getNumOfCorrectAnswers(username))); // correct answers
	std::vector<int> answerTimes = this->m_database->getPlayerTimesToAnswer(username);
	int sum = 0;
	for (int i = 0; i < answerTimes.size(); i++)
	{
		sum += answerTimes[i];
	}
	//std::vector<int> averageRightTimes = this->m_database.getPlayerAnswerTimes(username);
	statistics.push_back(std::to_string(sum / answerTimes.size())); // Average answer time 
	return statistics;
}

int StatisticsManager::getUserScore(std::string username)
{
	// formula: [(1 - (({response time} / {question timer}}) / 2)) * 1000]
	// average question score * number of questions
	//return ((1 - ((this->m_database->getPlayerAverageRightAnswerResponseTime(username) / this->m_database->getPlayerAverageRightAnswerTime(username)) / 2) * 1000) * this->m_database->getNumOfTotalAnswers(username));
	return this->getUserPoints(username);
}

int StatisticsManager::getUserPoints(std::string username)
{
	int sum = 0;
	char** errMessage = nullptr;
	std::vector<int> timeForQuestion = this->m_database->getPlayerTimesForQuestions(username);
	std::vector<int> answerTimes = this->m_database->getPlayerTimesToAnswer(username);
	for (int i = 0; i < timeForQuestion.size(); i++)
	{
		sum += (1 - (((float)answerTimes[i] / timeForQuestion[i]) / 2)) * 1000;
	}
	return sum;
}
