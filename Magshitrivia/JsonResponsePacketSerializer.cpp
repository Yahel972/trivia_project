#include "JsonResponsePacketSerializer.h"

// function serializes a login response - converts the LoginResponse struct to bytes (unsigned char vector)
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, LOGIN_CODE));
}

// function serializes a signup response - converts the SignupResponse struct to bytes (unsigned char vector)
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, SIGNUP_CODE));
}

// function serializes an error response - converts the ErrorResponse struct to bytes (unsigned char vector)
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"message",response.message} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, ERROR_CODE));
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, LOGOUT_CODE));
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse response)
{
	std::vector<unsigned char> serializedResponse;
	std::string rooms = "";
	for (auto room : response.rooms) {
		rooms += room.name;
		rooms += ",";
	}
	nlohmann::json j = nlohmann::json{ {"status",response.status}, {"Rooms",rooms} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, GET_ROOMS));
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse response)
{
	std::vector<unsigned char> serializedResponse;
	std::string players = "";
	for (auto player : response.players) {
		players += player;
		players += ",";
	}
	nlohmann::json j = nlohmann::json{ {"PlayersInRoom:",players} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, GET_PLAYERS_IN_ROOM));
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, JOIN_ROOM));
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, CREATE_ROOM));
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse response)
{
	std::vector<unsigned char> serializedResponse;
	std::string highScores = "";
	for (auto score : response.statistics) {
		highScores += score;
		highScores += ",";
	}
	nlohmann::json j = nlohmann::json{ {"status",response.status}, {"HighScores",highScores} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, GET_HIGH_SCORES));
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResponse response)
{
	std::vector<unsigned char> serializedResponse;
	std::string userStatistics = "";
	for (auto statistic : response.statistics) {
		userStatistics += statistic;
		userStatistics += ",";
	}
	nlohmann::json j = nlohmann::json{ {"status",response.status}, {"UserStatistics",userStatistics} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, GET_USER_STATISTICS));
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, CLOSE_ROOM));
}
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(StartGameResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, START_GAME));
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse response)
{
	std::vector<unsigned char> serializedResponse;
	//nlohmann::json j = nlohmann::json{ {"status",response.status}, {"hasGameBegun",response.hasGameBegun.toString()}, { };
	return serializedResponse;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	return (JsonResponsePacketSerializer::generalSerialize(jsonAsBytes, LEAVE_ROOM));
}


std::vector<unsigned char> JsonResponsePacketSerializer::generalSerialize(std::vector<unsigned char> jsonAsBytes, int code)
{
	std::vector<unsigned char> serializedResponse;
	unsigned int lengthAsInt = (jsonAsBytes.size());
	unsigned char lengthAsBytes[4];
	lengthAsBytes[0] = (lengthAsInt >> 24) & 0xFF;
	lengthAsBytes[1] = (lengthAsInt >> 16) & 0xFF;
	lengthAsBytes[2] = (lengthAsInt >> 8) & 0xFF;
	lengthAsBytes[3] = lengthAsInt & 0xFF;
	serializedResponse.push_back(((unsigned char)code));

	// pushing data length
	for (int i = 0; i < sizeof(lengthAsBytes); i++)
	{
		serializedResponse.push_back(lengthAsBytes[i]);
	}

	for (int i = 0; i < lengthAsInt; i++)
	{
		serializedResponse.push_back(jsonAsBytes[i]);
	}

	return serializedResponse;
}
