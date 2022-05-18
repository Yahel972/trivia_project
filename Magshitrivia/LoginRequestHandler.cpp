#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler()
{
	this->m_loginManager = LoginManager();
	this->m_handlerFactory = RequestHandlerFactory();
}

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
		SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignUpRequest(request.buffer); // the request
		this->m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email); // signing up
		// if signup was succesfull
		SignupResponse signupResonse = { OK };
		RequestResult result;
		result.newHandler = new LoginRequestHandler;
		result.response = JsonResponsePacketSerializer::serializeSignupResponse(signupResonse);
		// else

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

RequestResult LoginRequestHandler::login(RequestInfo request)
{
	return RequestResult();
}
