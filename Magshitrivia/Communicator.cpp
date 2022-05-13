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
	sa.sin_port = htons(SERVER_PORT);  // port that server will listen for
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;  // when there are few ip's for the machine. We will use always "INADDR_ANY"

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
	while (true)
	{
		char recivedData[MAX_SIZE] = { 0 };
		recv(socket, recivedData, MAX_SIZE, 0);

		RequestInfo requestInfo;
		requestInfo.id = (int)(recivedData[0]);
		int dataLength = recivedData[1] << 24 | recivedData[2] << 16 | recivedData[3] << 8 | recivedData[4];
		requestInfo.receivalTime = time(NULL);

		// pushing data to vector
		for (int i = DATA_STARTING_BYTE; i < dataLength + DATA_STARTING_BYTE; i++)
		{
			requestInfo.buffer.push_back(((unsigned char)recivedData[i]));
		}

		// checking if the request given is valid
		if (this->m_clients[socket]->isRequestRelevant(requestInfo))
		{
			RequestResult result = this->m_clients[socket]->handleRequest(requestInfo);
			delete this->m_clients[socket];
			this->m_clients[socket] = result.newHandler;
			std::stringstream responseStream;
			for (int i = 0; i < result.response.size(); i++)
			{
				responseStream << result.response[i];
			}
			send(socket, responseStream.str().c_str(), responseStream.str().size(), 0);
		}
		else  // invalid request given
		{
			ErrorResponse errorResponse;
			errorResponse.message = "ERROR wrong code";
			std::vector<unsigned char> serializedResponse = JsonResponsePacketSerializer::serializeErrorResponse(errorResponse);
			std::stringstream responseStream;
			for (int i = 0; i < serializedResponse.size(); i++)
			{
				responseStream << serializedResponse[i];
			}
			send(socket, responseStream.str().c_str(), responseStream.str().size(), 0);
		}
	}
}
