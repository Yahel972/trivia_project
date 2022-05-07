#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == 100 || request.id == 200);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
	return RequestResult();
}
