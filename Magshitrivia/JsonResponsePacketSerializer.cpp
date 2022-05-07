#include "JsonResponsePacketSerializer.h"

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBits = nlohmann::json::to_bson(j);
	unsigned int lengthAsInt = (jsonAsBits.size() / 8);
	unsigned char lengthAsBytes[4];
	lengthAsBytes[0] = (lengthAsInt >> 24) & 0xFF;
	lengthAsBytes[1] = (lengthAsInt >> 16) & 0xFF;
	lengthAsBytes[2] = (lengthAsInt >> 8) & 0xFF;
	lengthAsBytes[3] = lengthAsInt & 0xFF;
	serializedResponse.push_back(((unsigned char)LOGIN_CODE));

	// pushing data length
	for (int i = 0; i < sizeof(lengthAsBytes); i++)
	{
		serializedResponse.push_back(lengthAsBytes[i]);
	}

	for (int i = 0; i < jsonAsBits.size(); i++)
	{
		serializedResponse.push_back(jsonAsBits[i]);
	}
	return serializedResponse;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	unsigned int lengthAsInt = (jsonAsBytes.size() / 8);
	unsigned char lengthAsBytes[4];
	lengthAsBytes[0] = (lengthAsInt >> 24) & 0xFF;
	lengthAsBytes[1] = (lengthAsInt >> 16) & 0xFF;
	lengthAsBytes[2] = (lengthAsInt >> 8) & 0xFF;
	lengthAsBytes[3] = lengthAsInt & 0xFF;
	serializedResponse.push_back(((unsigned char)LOGIN_CODE));
	for (int i = 0; i < sizeof(lengthAsBytes); i++)
	{
		serializedResponse.push_back(lengthAsBytes[i]);
	}
	for (int i = 0; i < jsonAsBytes.size(); i++)
	{
		serializedResponse.push_back(jsonAsBytes[i]);
	}
	return serializedResponse;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"message",response.message} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	unsigned int lengthAsInt = (jsonAsBytes.size() / 8);
	unsigned char lengthAsBytes[4];
	lengthAsBytes[0] = (lengthAsInt >> 24) & 0xFF;
	lengthAsBytes[1] = (lengthAsInt >> 16) & 0xFF;
	lengthAsBytes[2] = (lengthAsInt >> 8) & 0xFF;
	lengthAsBytes[3] = lengthAsInt & 0xFF;
	serializedResponse.push_back(((unsigned char)LOGIN_CODE));
	for (int i = 0; i < sizeof(lengthAsBytes); i++)
	{
		serializedResponse.push_back(lengthAsBytes[i]);
	}
	for (int i = 0; i < jsonAsBytes.size(); i++)
	{
		serializedResponse.push_back(jsonAsBytes[i]);
	}

	return serializedResponse;
}
