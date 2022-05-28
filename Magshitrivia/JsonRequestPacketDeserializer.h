#pragma once
#include <iostream>
#include <vector>
#include "single_include/nlohmann/json.hpp"

typedef struct LoginRequest
{
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
} SignupRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
} CreateRoomRequest;

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
} JoinRoomRequest;



class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> Buffer);
	static SignupRequest deserializeSignUpRequest(std::vector<unsigned char> Buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char> Buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> Buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> Buffer);
};