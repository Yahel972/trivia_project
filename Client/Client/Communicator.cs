using Newtonsoft.Json;
using Newtonsoft.Json.Bson;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client
{
    public class SignUpMessage
    {
        public string username { get; set; }
        public string password { get; set; }
        public string email { get; set; }
    }

    public class LoginMessage
    {
        public string username { get; set; }
        public string password { get; set; }
    }

    public class createRoomMessage
    {
        public string roomName { get; set; }
        public uint maxUsers { get; set; }
        public uint questionCount { get; set; }
        public uint answerTimeout { get; set; }
    }

    public class joinRoomMessage
    {
        public uint roomId { get; set; }
    }

    public class getPlayersInRoomMessage
    {
        public uint roomId { get; set; }
    }



    public class OnlyStatusResponse
    {
        public uint status { get; set; }
    }

    public class getStatisticsResponse
    {
        public uint status { get; set; }
        public List<string> statistics { get; set; }
    }

    public class RoomData
    {
        public uint id { get; set; }
        public string name { get; set; }
        public uint maxPlayers { get; set; }
        public uint numOfQuestions { get; set; }
        public uint timePerQuestion { get; set; }
        public uint isActive { get; set; }
    }

    public class GetRoomsResponse
    {
        public uint status { get; set; }
        public List<RoomData> Rooms { get; set; }
    }
    public class GetRoomStatusResponse
    {
        public uint status { get; set; }
        public bool hasGameBegun { get; set; }
        public List<string> players { get; set; }
        public uint questionCount { get; set; }
        public uint answerTimeout { get; set; }
    }

    public class GetPlayersInRoomResponse
    {
        public uint status { get; set; }
        public List<string> players { get; set; }
    }

    class Communicator
    {
        public TcpClient client;
        IPEndPoint serverEndPoint;
        NetworkStream clientStream;
        public Communicator()
        {
            this.client = new TcpClient();
            this.serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 6969);
            client.Connect(serverEndPoint);
            this.clientStream = client.GetStream();
        }

        public void sendMessage(byte[] message)
        {
            clientStream.Write(message, 0, message.Length);
            clientStream.Flush();
        }

        public byte[] getSignupMessage(string username, string password, string email)
        {
            var signup = new SignUpMessage
            {
                username = username,
                password = password,
                email = email
            };
            MemoryStream ms = new MemoryStream();
            using (BsonWriter writer = new BsonWriter(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                serializer.Serialize(writer, signup);
            }
            byte[] data = ms.ToArray();
            byte[] firstPart = this.getFirstMessagePart(1, data.Length);
            byte[] buffer = firstPart.Concat(data).ToArray();
            return buffer;
        }

        public byte[] getLoginMessage(string username, string password)
        {
            var login = new LoginMessage
            {
                username = username,
                password = password
            };
            MemoryStream ms = new MemoryStream();
            using (BsonWriter writer = new BsonWriter(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                serializer.Serialize(writer, login);
            }
            byte[] data = ms.ToArray();
            byte[] firstPart = this.getFirstMessagePart(2, data.Length);
            byte[] buffer = firstPart.Concat(data).ToArray();
            return buffer;
        }

        public byte[] getCreateRoomMessage(string roomName, uint maxUsers, uint answerTimeout, uint questionCount)
        {
            var createRoom = new createRoomMessage
            {
                roomName = roomName,
                maxUsers = maxUsers,
                answerTimeout = answerTimeout,
                questionCount = questionCount
            };
            MemoryStream ms = new MemoryStream();
            using (BsonWriter writer = new BsonWriter(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                serializer.Serialize(writer, createRoom);
            }
            byte[] data = ms.ToArray();
            byte[] firstPart = this.getFirstMessagePart(4, data.Length);
            byte[] buffer = firstPart.Concat(data).ToArray();
            return buffer;
        }

        public byte[] getJoinRoomMessage(uint roomId)
        {
            var joinRoom = new joinRoomMessage
            {
                roomId = roomId
            };
            MemoryStream ms = new MemoryStream();
            using (BsonWriter writer = new BsonWriter(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                serializer.Serialize(writer, joinRoom);
            }
            byte[] data = ms.ToArray();
            byte[] firstPart = this.getFirstMessagePart(5, data.Length);
            byte[] buffer = firstPart.Concat(data).ToArray();
            return buffer;
        }

        public byte[] getPlayersInRoomMessage(uint roomId)
        {
            var joinRoom = new getPlayersInRoomMessage
            {
                roomId = roomId
            };
            MemoryStream ms = new MemoryStream();
            using (BsonWriter writer = new BsonWriter(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                serializer.Serialize(writer, joinRoom);
            }
            byte[] data = ms.ToArray();
            byte[] firstPart = this.getFirstMessagePart(7, data.Length);
            byte[] buffer = firstPart.Concat(data).ToArray();
            return buffer;
        }
        public byte[] getNoDataMessage(int code) // logout, getRooms, getHighScores, getUserStatistics
        {
            byte[] data = new byte[] { };
            byte[] firstPart = this.getFirstMessagePart(code, data.Length);
            byte[] buffer = firstPart.Concat(data).ToArray();
            return buffer;
        }

        public byte[] reciveResponse()
        {
            byte[] response = new byte[4101];
            byte[] onlyData = new byte[4096];
            int bytesRead = this.clientStream.Read(response, 0, 4096);
            int index = 0;
            for(int i = 5; i < response.Length; i++)
            {
                onlyData[index] = response[i];
                index++;
            }
            return onlyData;
        }

        public OnlyStatusResponse getGeneralResponse(byte[] buffer)
        {
            MemoryStream ms = new MemoryStream(buffer);
            OnlyStatusResponse response;
            using (BsonReader reader = new BsonReader(ms))
            {
                JsonSerializer serializer = new JsonSerializer();

                response = serializer.Deserialize<OnlyStatusResponse>(reader);
            }
            return response;
        }

        public getStatisticsResponse getStatisticsResponse(byte[] buffer)
        {
            MemoryStream ms = new MemoryStream(buffer);
            getStatisticsResponse response;
            using (BsonReader reader = new BsonReader(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                response = serializer.Deserialize<getStatisticsResponse>(reader);
            }
            return response;
        }

        public GetRoomsResponse getRoomsResponse(byte[] buffer)
        {
            MemoryStream ms = new MemoryStream(buffer);
            GetRoomsResponse response;
            using (BsonReader reader = new BsonReader(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                response = serializer.Deserialize<GetRoomsResponse>(reader);
            }
            return response;
        }

        public GetRoomStatusResponse getRoomStatusResponse(byte[] buffer)
        {
            MemoryStream ms = new MemoryStream(buffer);
            GetRoomStatusResponse response;
            using (BsonReader reader = new BsonReader(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                response = serializer.Deserialize<GetRoomStatusResponse>(reader);
            }
            return response;
        }

        public GetPlayersInRoomResponse getPlayersInRoomResponse(byte[] buffer)
        {
            MemoryStream ms = new MemoryStream(buffer);
            GetPlayersInRoomResponse response;
            using (BsonReader reader = new BsonReader(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                response = serializer.Deserialize<GetPlayersInRoomResponse>(reader);
            }
            return response;
        }

        private byte[] getFirstMessagePart(int code, int dataLength)
        {
            byte[] firstPart = new byte[5];
            firstPart[0] = BitConverter.GetBytes(code)[0];
            firstPart[1] = (byte)(dataLength >> 24);
            firstPart[2] = (byte)(dataLength >> 16);
            firstPart[3] = (byte)(dataLength >> 8);
            firstPart[4] = (byte)(dataLength);
            return firstPart;
        }

    }
}
