#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

class SqliteDataBase : public IDatabase
{
public:
	bool open() override; // for creating the database
	bool doesUserExist(std::string user) override;
	bool doesPasswordMatch(std::string enterdPassword, std::string passwordToMatch) override;
	void addNewUser(std::string name, std::string password, std::string email) override;
private:
	sqlite3* db;
	static int callback_user(void* data, int argc, char** argv, char** azColName);
	static int callback_password(void* data, int argc, char** argv, char** azColName);
};