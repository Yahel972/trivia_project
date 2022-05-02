#pragma once

#include <vector>
#include <iostream>
#include <time.h>

typedef struct RequestResult
{
	std::vector<unsigned char> response;
	//IRequestHandler* newHandler;
} RequestResult;

typedef struct RequestInfo
{
	unsigned char id;
	time_t receivalTime;
	std::vector<unsigned char> buffer;
} RequestInfo;

class IRequestHandler
{
public:
	bool isRequest();

};
