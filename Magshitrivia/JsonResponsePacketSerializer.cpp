#include "JsonResponsePacketSerializer.h"

// function serializes a login response - converts the LoginResponse struct to bytes (unsigned char vector)
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	unsigned int lengthAsInt = (jsonAsBytes.size());
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

	for (int i = 0; i < lengthAsInt; i++)
	{
		serializedResponse.push_back(jsonAsBytes[i]);
	}

	return serializedResponse;
}

// function serializes a signup response - converts the SignupResponse struct to bytes (unsigned char vector)
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"status",response.status} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	unsigned int lengthAsInt = (jsonAsBytes.size());
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

	for (int i = 0; i < lengthAsInt; i++)
	{
		serializedResponse.push_back(jsonAsBytes[i]);
	}
	return serializedResponse;
}

// function serializes an error response - converts the ErrorResponse struct to bytes (unsigned char vector)
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
	std::vector<unsigned char> serializedResponse;
	nlohmann::json j = nlohmann::json{ {"message",response.message} };
	std::vector<unsigned char> jsonAsBytes = nlohmann::json::to_bson(j);
	unsigned int lengthAsInt = (jsonAsBytes.size());
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

	for (int i = 0; i < lengthAsInt; i++)
	{
		serializedResponse.push_back(jsonAsBytes[i]);
	}
	return serializedResponse;
}
