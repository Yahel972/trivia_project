#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"


class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo request) const;
	RequestResult handleRequest(RequestInfo request) const;
};
