#pragma once
#include <iostream>
#include <vector>
#include "single_include/nlohmann/json.hpp"

#define ERROR_CODE 3
#define LOGIN_CODE 2
#define SIGNUP_CODE 1
#define OK 1

typedef struct LoginResponse
{
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse
{
	std::string message;
} ErrorResponse;

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeLoginResponse(LoginResponse response);
	static std::vector<unsigned char> serializeSignupResponse(SignupResponse response);
	static std::vector<unsigned char> serializeErrorResponse(ErrorResponse response);
};
