#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == 100 || request.id == 200);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
	if (request.id == 100)
	{
		SignupResponse signupResonse = { 1 };
		RequestResult requstResult;
		requstResult.response = JsonResponsePacketSerializer::serializeSignupResponse(signupResonse);
		return requstResult;
	}
	if (request.id == 200)
	{
		LoginResponse loginResonse = { 1 };
		RequestResult requstResult;
		requstResult.response = JsonResponsePacketSerializer::serializeLoginResponse(loginResonse);
		return requstResult;
	}
}
