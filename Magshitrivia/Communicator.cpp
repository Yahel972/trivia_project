#include "Communicator.h"

/*
	Function accepts communication from user
	Input: none
	Output: none
*/
void Communicator::startHandleRequest()
{
	this->m_handlerFactory = RequestHandlerFactory(); // creating the handlerFactory
	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "Client accepted. Server and client can speak" << std::endl;
		this->m_clients[client_socket] = this->m_handlerFactory.createLoginRequest();
		// the function that handle the conversation with the client
		std::thread clientThread(&Communicator::handleNewClient, this, client_socket); // thread for each client
		clientThread.detach(); // no need to wait for client thread to end, it can run until the client logs out 
	}
}

/*
	Function binds server socket and start listening for incoming requests of clients
	Input: none
	Output: none
*/
void Communicator::bindAndListen()
{
	std::cout << "Starting..." << std::endl;
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // new Socket

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

/*
	Function handles new connecting client
	Input: the socket of the new client
	Output: none
*/
void Communicator::handleNewClient(SOCKET socket)
{
	// checking if the new RequestInfo is relevent 
	// if the RequestInfo IS relevent, handle it
	// receving data 
	while (true) // keeping communication alive
	{
		// reciving message
		char recivedData[MAX_SIZE] = { 0 };
		recv(socket, recivedData, MAX_SIZE, 0);

		// parsing into the struct "RequsetInfo"
		RequestInfo requestInfo;
		requestInfo.id = (int)(recivedData[0]);
		int dataLength = recivedData[1] << 24 | recivedData[2] << 16 | recivedData[3] << 8 | recivedData[4];
		requestInfo.receivalTime = time(NULL);
		for (int i = DATA_STARTING_BYTE; i < dataLength + DATA_STARTING_BYTE; i++) // pushing the data part to speical field
		{
			requestInfo.buffer.push_back(((unsigned char)recivedData[i]));
		}

		// handeling the request
		if (this->m_clients[socket]->isRequestRelevant(requestInfo)) // checking if the given request is valid based on the current state of the user 
		{
			RequestResult result = this->m_clients[socket]->handleRequest(requestInfo); // handleing requset
			
			// switching (or, not switching) the current state of the user
			if (result.newHandler != nullptr)
			{
				delete this->m_clients[socket];
				this->m_clients[socket] = result.newHandler;
			}
			
			// sending the response back to the client
			std::stringstream responseStream;
			for (int i = 0; i < result.response.size(); i++)
			{
				responseStream << result.response[i];
			}
			send(socket, responseStream.str().c_str(), responseStream.str().size(), 0);
		}
		else  // invalid request for the current state 
		{
			// building and sending error message
			ErrorResponse errorResponse;
			errorResponse.message = "ERROR wrong code (" + std::to_string(requestInfo.id) + ") for current state";
			std::vector<unsigned char> serializedResponse = JsonResponsePacketSerializer::serializeResponse(errorResponse);
			std::stringstream responseStream;
			for (int i = 0; i < serializedResponse.size(); i++)
			{
				responseStream << serializedResponse[i];
			}
			send(socket, responseStream.str().c_str(), responseStream.str().size(), 0);
		}
	}
}
