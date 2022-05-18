#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler():m_loginManager(* new LoginManager), m_handlerFactory(* new RequestHandlerFactory)
{

}

// function checks if a given request is relevant
bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	return (request.id == SIGNUP_CODE || request.id == LOGIN_CODE);
}

// function handles a request by its given code
RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
	if (request.id == SIGNUP_CODE)
	{
		return (this->signup(request));
	}
	if (request.id == LOGIN_CODE)
	{

		return result;
	}
}

RequestResult LoginRequestHandler::login(RequestInfo request)
{
	SignupRequest loginRequest = JsonRequestPacketDeserializer::deserializeSignUpRequest(request.buffer); // the request
	this->m_loginManager.login(loginRequest.username, loginRequest.password); // signing up
	RequestResult result;
	if (1 == 1)
	{
		LoginResponse loginResonse = { OK };
		result.newHandler = new LoginRequestHandler;
		result.response = JsonResponsePacketSerializer::serializeLoginResponse(loginResonse);
	}
	else
	{
		LoginResponse loginResponse = { 0 };
		result.newHandler = nullptr;
		result.response = JsonResponsePacketSerializer::serializeLoginResponse(loginResponse);
	}
	return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo request)
{
	SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignUpRequest(request.buffer); // the request
	this->m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email); // signing up
	RequestResult result;
	// if signup was succesfull
	if (1 == 1)
	{
		SignupResponse signupResonse = { OK };
		result.newHandler = new LoginRequestHandler; // DONT FORGET CHANGE TO MenuRequestHandler
		result.response = JsonResponsePacketSerializer::serializeSignupResponse(signupResonse);
	}
	else
	{
		SignupResponse signupResonse = { 0 };
		result.newHandler = nullptr;
		result.response = JsonResponsePacketSerializer::serializeSignupResponse(signupResonse);
	}

	// else
	// signup resonse not ok
	// request.newHandler = null
	return result;
}
