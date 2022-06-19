#pragma once
#include <vector>
#include <iostream>
#include <time.h>

typedef struct RequestInfo
{
	unsigned char id; // the code of the request (request identifier)
	time_t receivalTime; // the time the request was recived in
	std::vector<unsigned char> buffer; // the requests itself (the data)
} RequestInfo;

struct RequestResult; // for diamond problems

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo request) = 0; // checking if the request is relevant for the current user state
	virtual RequestResult handleRequest(RequestInfo request) = 0; // handeling the request
};

typedef struct RequestResult
{
	std::vector<unsigned char> response; // the response itself (the data)
	IRequestHandler* newHandler; // the new user state
} RequestResult;