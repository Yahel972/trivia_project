#pragma once
#include <iostream>
#include <vector>
#include "single_include/nlohmann/json.hpp"

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
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> Buffer);
	static SignupRequest deserializeSignUpRequest(std::vector<unsigned char> Buffer);
};