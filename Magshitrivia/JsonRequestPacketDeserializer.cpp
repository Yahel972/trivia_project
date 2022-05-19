#include "JsonRequestPacketDeserializer.h"

// function deserializes a login request - converts the bytes (unsigned char vector) to LoginRequest struct
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> Buffer)
{
	std::vector<unsigned char> jsonAsBytes;
	nlohmann::json j = nlohmann::json::from_bson(Buffer);
	LoginRequest request = { j["username"].get<std::string>(),  j["password"].get<std::string>() };
	return request;
}

// function deserializes a signup request - converts the bytes (unsigned char vector) to SignupRequest struct
SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<unsigned char> Buffer)
{
	std::vector<unsigned char> jsonAsBytes;
	nlohmann::json j = nlohmann::json::from_bson(Buffer);
	SignupRequest request = { j["username"].get<std::string>(), j["password"].get<std::string>(), j["email"].get<std::string>() };
	return request;
}
