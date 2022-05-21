#pragma once
#include <iostream>
#include <vector>
#include "single_include/nlohmann/json.hpp"
#include "Room.h"

#define OK 1

#define ERROR_CODE 200

#define SIGNUP_CODE 1
#define LOGIN_CODE 2


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

typedef struct JoinRoomResponse
{
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
} CreateRoomResponse;

typedef struct LogoutResponse
{
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct getHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
} GetRoomsResponse;

typedef struct getPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
} GetRoomsResponse;


class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeLoginResponse(LoginResponse response);
	static std::vector<unsigned char> serializeSignupResponse(SignupResponse response);
	static std::vector<unsigned char> serializeErrorResponse(ErrorResponse response);
};
