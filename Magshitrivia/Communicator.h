#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <thread>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

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