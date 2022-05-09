#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == 1 || request.id == 2);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
	if (request.id == 1)
	{
		SignupResponse signupResonse = { 1 };
		RequestResult result;
		result.newHandler = new LoginRequestHandler;
		result.response = JsonResponsePacketSerializer::serializeSignupResponse(signupResonse);
		return result;
	}
	if (request.id == 2)
	{
		LoginResponse loginResonse = { 1 };
		RequestResult result;
		result.newHandler = new LoginRequestHandler;
		result.response = JsonResponsePacketSerializer::serializeLoginResponse(loginResonse);
		return result;
	}
}
