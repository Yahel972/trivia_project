#include "LoginRequestHandler.h"

// function checks if a given request is relevant
bool LoginRequestHandler::isRequestRelevant(RequestInfo request) const
{
	return (request.id == SIGNUP_CODE || request.id == LOGIN_CODE);
}

// function handles a request by its given code
RequestResult LoginRequestHandler::handleRequest(RequestInfo request) const
{
	if (request.id == SIGNUP_CODE)
	{
		SignupResponse signupResonse = { OK };
		RequestResult result;
		result.newHandler = new LoginRequestHandler;
		result.response = JsonResponsePacketSerializer::serializeSignupResponse(signupResonse);
		return result;
	}
	if (request.id == LOGIN_CODE)
	{
		LoginResponse loginResonse = { OK };
		RequestResult result;
		result.newHandler = new LoginRequestHandler;
		result.response = JsonResponsePacketSerializer::serializeLoginResponse(loginResonse);
		return result;
	}
}
