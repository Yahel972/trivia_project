#pragma once
#include <iostream>

typedef struct LoginRequest
{
	std::string username;
	std::string password;
} LoginResponse;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
} SignupResponse;


class JsonRequestPacketDeserializer
{
public:
	
};