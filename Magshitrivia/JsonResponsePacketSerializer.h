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
#define CLOSE_ROOM 10
#define START_GAME 11
#define GET_ROOM_STATE 12
#define LEAVE_ROOM 13
#define LEAVE_GAME 14
#define GET_QUESTION 15
#define SUBMIT_ANSWER 16
#define GET_GAME_RESULTS 17

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
	unsigned int status;
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

typedef struct CloseRoomResponse
{
	unsigned int status;
} CloseRoomResponse;

typedef struct StartGameResponse
{
	unsigned int status;
} StartGameResponse;

typedef struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse
{
	unsigned int status;
} LeaveRoomResponse;

typedef struct LeaveGameResponse
{
	unsigned int status;
} LeaveGameResponse;

typedef struct GetQuestionResponse
{
	unsigned int status;
	std::string question;
	std::vector<std::string> answers;
} GetQuestionResponse;

typedef struct SubmitAnswerResponse
{
	unsigned int status;
	std::string rightAnswer;
} SubmitAnswerResponse;

typedef struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
} PlayerResults;

typedef struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
} GetGameResultsResponse;


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
	static std::vector<unsigned char> serializeResponse(CloseRoomResponse response);
	static std::vector<unsigned char> serializeResponse(StartGameResponse response);
	static std::vector<unsigned char> serializeResponse(GetRoomStateResponse response);
	static std::vector<unsigned char> serializeResponse(LeaveRoomResponse response);
	static std::vector<unsigned char> serializeResponse(LeaveGameResponse response);
	static std::vector<unsigned char> serializeResponse(GetQuestionResponse response);
	static std::vector<unsigned char> serializeResponse(SubmitAnswerResponse response);
	static std::vector<unsigned char> serializeResponse(GetGameResultsResponse response);
private:
	static std::vector<unsigned char> generalSerialize(std::vector<unsigned char> jsonAsBytes, int code);
	static void to_json(nlohmann::json& j, const RoomData& r);
	static void to_json(nlohmann::json& j, const PlayerResults& r);
};
