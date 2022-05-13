#include "SqliteDataBase.h"
#include <io.h>


bool SqliteDataBase::open()
{
	std::string dbFileName = "galleryDB.sqlite";
	char** errorMessage = 0;
	int file_exist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &(this->db));
	if (res != SQLITE_OK) {
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	if (file_exist != 0) {

		// creating the users table
		const char* sqlStatement = "CREATE TABLE USERS ( \
			USERNAME TEXT NOT NULL, \
			PASSWORD TEXT NOT NULL, \
			EMAIL TEXT NOT NULL);";
		res = sqlite3_exec(this->db, sqlStatement, nullptr, nullptr, errorMessage);
		if (res != SQLITE_OK)
			std::cout << "USERS wasn't created (maybe it already exists)" << std::endl;
	}
	else
	{
		
	}
	return true;
}

bool SqliteDataBase::doesUserExist(std::string user)
{
	return false;
}

bool SqliteDataBase::doesPasswordMatch(std::string enterdPassword, std::string passwordToMatch)
{
	return false;
}

void SqliteDataBase::addNewUser(std::string name, std::string password, std::string email)
{

}
