#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> Buffer)
{
	std::vector<unsigned char> jsonAsBytes;
	int lengthAsInt = (int)(Buffer[1] << 24 | Buffer[2] << 16 | Buffer[3] << 8 | Buffer[4]);
	for (int i = 5; i < Buffer.size(); i++)
	{
		jsonAsBytes.push_back(Buffer[i]);
	}
	nlohmann::json j = nlohmann::json::from_bson(jsonAsBytes);
	LoginRequest request = { j["username"].get<std::string>(),  j["password"].get<std::string>() };
	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<unsigned char> Buffer)
{
	std::vector<unsigned char> jsonAsBytes;
	int lengthAsIntBytes2 = (int)(Buffer[1] << 24 | Buffer[2] << 16 | Buffer[3] << 8 | Buffer[4]) * 8;
	for (int i = 5; i < Buffer.size(); i++)
	{
		jsonAsBytes.push_back(Buffer[i]);
	}
	nlohmann::json j = nlohmann::json::from_bson(jsonAsBytes);
	SignupRequest request = { j["username"].get<std::string>(),  j["password"].get<std::string>(), j["email"].get<std::string>() };
	return request;
}
