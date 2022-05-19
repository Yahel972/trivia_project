import socket
import bson

HOST_IP = "127.0.0.1"  # The server's hostname or IP address
SERVER_PORT = 6969  # The port used by the server


def main():

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST_IP, SERVER_PORT))

        # code = 2
        # json = {"username": "user1", "password": "1234"}
        # msg = getMessage(code, json)
        # s.sendall(msg)
        # test = s.recv(1024)
        # responseData1 = test[5:]
        # print(bson.loads(responseData1))

        code = 1
        json = {"username": "user1", "password": "1234", "email": "user1@gmail.com"}
        msg = getMessage(code, json)
        sendMessage(msg, s)

        code = 2
        json = {"username": "user1", "password": "1234"}
        msg = getMessage(code, json)
        sendMessage(msg, s)
        sendMessage(msg, s)
        

def getMessage(code, json):
    data = bson.dumps(json)
    msg = code.to_bytes(1, byteorder='big') + (len(data)).to_bytes(4, byteorder='big') + data
    return msg

def sendMessage(msg, sock):
    sock.sendall(msg)
    response = (sock.recv(1024))[5:]
    print(bson.loads(response))

if __name__ == '__main__':
    main()
