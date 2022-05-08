#include "Communicator.h"

void Communicator::startHandleRequest()
{
	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "Client accepted. Server and client can speak" << std::endl;
		this->m_clients[client_socket] = new LoginRequestHandler();
		// the function that handle the conversation with the client
		std::thread clientThread(&Communicator::handleNewClient, this, client_socket); // thread for each client
		clientThread.detach(); // no need to wait for client thread to end, it can run until the client logs out 
	}
}

void Communicator::bindAndListen()
{
	std::cout << "Starting..." << std::endl;
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");

	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(6969); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	std::cout << "Binded" << std::endl;

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");

	startHandleRequest();
}

void Communicator::handleNewClient(SOCKET socket)
{
	// reciving message and parsing into the struct "RequsetInfo"
	// checking if the new RequestInfo is relevent 
	// if the RequestInfo IS relevent, handle it

	// receving data 
	char recivedData[1000] = { '\0' };
	recv(socket, recivedData, 1000, 0);

	// getting the data to request info struct
	RequestInfo requestInfo;
	requestInfo.id = (int)(recivedData[0] << 16) | (recivedData[1] << 8) | recivedData[2];
	requestInfo.receivalTime = time(NULL);
	int length = (int)(recivedData[1] << 24 | recivedData[2] << 16 | recivedData[3] << 8 | recivedData[4]) * 8;
	for (int i = 3; i < length; i++)
	{
		requestInfo.buffer.push_back(recivedData[i]);
	}

	std::string message = "Hello";
	const char* data = message.c_str();
	if (send(socket, data, message.size(), 0) == INVALID_SOCKET)
	{
		std::cout << "Error while sending message to client" << std::endl;
	}
	
	std::cout << recivedData << std::endl;
}
