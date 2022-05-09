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

struct RequestResult;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo request) const = 0;
	virtual RequestResult handleRequest(RequestInfo request) const = 0;
};

typedef struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
} RequestResult;