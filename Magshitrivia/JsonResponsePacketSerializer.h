#pragma once
#include <iostream>
#include <vector>
#include "single_include/nlohmann/json.hpp"
#include "Room.h"

#define OK 1

#define ERROR_CODE 200

#define SIGNUP_CODE 1
#define LOGIN_CODE 2
#define LOGOUT_CODE 3
#define CREATE_ROOM 4
#define JOIN_ROOM 5
#define GET_ROOMS 6
#define GET_PLAYERS_IN_ROOM 7
#define GET_HIGH_SCORES 8
#define GET_USER_STATISTICS 9

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
} getHighScoreResponse;

typedef struct getPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
} getPersonalStatsResponse;


class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(LoginResponse response);
	static std::vector<unsigned char> serializeResponse(SignupResponse response);
	static std::vector<unsigned char> serializeResponse(ErrorResponse response);
	static std::vector<unsigned char> serializeResponse(LogoutResponse response);
	static std::vector<unsigned char> serializeResponse(GetRoomsResponse response);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse response);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse response);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse response);
	static std::vector<unsigned char> serializeResponse(getHighScoreResponse response);
	static std::vector<unsigned char> serializeResponse(getPersonalStatsResponse response);
private:
	static std::vector<unsigned char> generalSerialize(std::vector<unsigned char> jsonAsBytes, int code);
};
