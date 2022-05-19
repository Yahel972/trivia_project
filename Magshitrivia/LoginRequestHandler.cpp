#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory):m_loginManager(loginManager), m_handlerFactory(handlerFactory)
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

		return (this->login(request));;
	}
}

RequestResult LoginRequestHandler::login(RequestInfo request)
{
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer); // the request
	RequestResult result;
	if(this->m_loginManager.login(loginRequest.username, loginRequest.password))
	{
		LoginResponse loginResonse = { OK };
		result.newHandler = new MenuRequestHandler();
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
	RequestResult result;
	// if signup was succesfull
	if (this->m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email))
	{
		SignupResponse signupResonse = { OK };
		result.newHandler = new MenuRequestHandler();
		result.response = JsonResponsePacketSerializer::serializeSignupResponse(signupResonse);
	}
	else
	{
		SignupResponse signupResonse = { 0 };
		result.newHandler = nullptr;
		result.response = JsonResponsePacketSerializer::serializeSignupResponse(signupResonse);
	}
	return result;
}
