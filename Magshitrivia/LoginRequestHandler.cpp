#include "LoginRequestHandler.h"

// constructor
LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory):m_loginManager(loginManager), m_handlerFactory(handlerFactory)
{
	
}

// function checks if a given request is relevant (in this state- only login or signup)
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
		return (this->login(request));
	}
}

// function logs in user and returns response to the client
RequestResult LoginRequestHandler::login(RequestInfo request)
{
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer); // the request
	RequestResult result;
	int resultCode = this->m_loginManager.login(loginRequest.username, loginRequest.password);
	if(resultCode == OK)  // valid request
	{
		LoginResponse loginResonse = { OK };
		result.newHandler = this->m_handlerFactory.createMenuRequestHandler(loginRequest.username);
		result.response = JsonResponsePacketSerializer::serializeResponse(loginResonse);
	}
	else  // invalid request
	{
		LoginResponse loginResponse = { resultCode };
		result.newHandler = nullptr;
		result.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
	}
	return result;
}

// function signs up user and returns response to the client
RequestResult LoginRequestHandler::signup(RequestInfo request)
{
	SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignUpRequest(request.buffer); // the request
	RequestResult result;
	// if signup was succesfull
	if (this->m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email))
	{
		SignupResponse signupResonse = { OK };
		result.newHandler = this->m_handlerFactory.createMenuRequestHandler(signupRequest.username);
		result.response = JsonResponsePacketSerializer::serializeResponse(signupResonse);
	}
	else
	{
		SignupResponse signupResonse = { 0 };
		result.newHandler = nullptr;
		result.response = JsonResponsePacketSerializer::serializeResponse(signupResonse);
	}
	return result;
}
