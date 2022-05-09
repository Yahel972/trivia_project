#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <thread>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

#define SERVER_PORT 6969
#define MAX_SIZE 1024
#define DATA_STARTING_BYTE 5

class Communicator
{
public:
	void startHandleRequest();
	void bindAndListen();
private:
	void handleNewClient(SOCKET socket);
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
};
