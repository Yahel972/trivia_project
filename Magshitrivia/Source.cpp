#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include "WSAInitializer.h"
#include <iostream>
#include <exception>
#include "JsonResponsePacketSerializer.h"
#include "LoginRequestHandler.h"
#include "SqliteDataBase.h"
#include "LoginManager.h"


int main()
{
	// creating a server and running it:
	try
	{
		WSAInitializer wsaInit;
		Server myServer;
		myServer.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}
