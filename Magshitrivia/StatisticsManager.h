#pragma once
#include <iostream>
#include <vector>
#include "SqliteDataBase.h"
#include <string>
#include <algorithm>

class StatisticsManager
{
public:
	StatisticsManager();
	StatisticsManager(IDatabase* database);
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
private:
	int getUserScore(std::string username);
	int getUserPoints(std::string username);
	IDatabase* m_database;
	static bool sortbysec(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);

};