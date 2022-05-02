#pragma once

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);
};
