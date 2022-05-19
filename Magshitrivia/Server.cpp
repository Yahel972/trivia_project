#include "Server.h"


void Server::run()
{
	//this->m_handlerFactory = RequestHandlerFactory();
	//this->m_communicator.setHandlerFactory(this->m_handlerFactory);
	std::thread t_connector(&Communicator::bindAndListen, this->m_communicator);  // creating server
	t_connector.detach();
	std::string userInput = "";
	while (userInput != "EXIT")
	{
		std::cin >> userInput;
	}

}
