#pragma once
#include <iostream>
#include <vector>

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
	LoginRequest deserializeLoginRequest(std::vector<unsigned char> Buffer);
	SignupRequest deserializeSignUpRequest(std::vector<unsigned char> Buffer);
};