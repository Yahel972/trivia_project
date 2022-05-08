#pragma once

#include <vector>
#include <iostream>
#include <time.h>

typedef struct RequestInfo
{
	unsigned char id;
	time_t receivalTime;
	std::vector<unsigned char> buffer;
} RequestInfo;


class RequestResult
{
public:
	std::vector<unsigned char> response;
	IRequestHandler* newHandle;
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo request) = 0;
	virtual RequestResult handleRequest(RequestInfo request) = 0;
};
