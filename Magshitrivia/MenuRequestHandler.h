#pragma once
#include "IRequestHandler.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);
};
