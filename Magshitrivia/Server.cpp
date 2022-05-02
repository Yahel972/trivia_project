#include "Server.h"

void Server::run()
{
	std::thread t_connector(&Communicator::bindAndListen, this->m_communicator);
	t_connector.detach();
	std::string userInput = "";
	while (userInput != "EXIT")
	{
		std::cin >> userInput;
	}

}
