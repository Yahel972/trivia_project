import socket
import bson

HOST_IP = "127.0.0.1"  # The server's hostname or IP address
SERVER_PORT = 6969  # The port used by the server


def main():

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST_IP, SERVER_PORT))

        code = 2
        json = {"username": "Dean", "password": "Einer"}
        msg = getMessage(code, json)
        sendMessage(msg, s)

        code = 4
        json = {"roomName": "firstRoom", "maxUsers": 10, "questionCount": 5, "answerTimeout": 30}
        msg = getMessage(code, json)
        sendMessage(msg, s)

        code = 8
        json = {}
        msg = getMessage(code, json)
        sendMessage(msg, s)

        code = 3
        json = {}
        msg = getMessage(code, json)
        sendMessage(msg, s)

        code = 4
        json = {"roomName": "secondRoom", "maxUsers": 10, "questionCount": 5, "answerTimeout": 30}
        msg = getMessage(code, json)
        sendMessage(msg, s)

        code = 6
        json = {}
        msg = getMessage(code, json)
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
