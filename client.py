import socket
import bson

HOST_IP = "127.0.0.1"  # The server's hostname or IP address
SERVER_PORT = 6969  # The port used by the server


def main():
    code = 2
    json = {"username": "user1", "password": "1234"}
    data = bson.dumps(json)
    msg = code.to_bytes(1, byteorder='big') + (len(data)).to_bytes(4, byteorder='big') + data

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST_IP, SERVER_PORT))

        s.sendall(msg)
        #code = 1
        #json = b'{username: "user1", password: "1234", mail: "user1@gmail.com"}'
        #msg = code.to_bytes(1, byteorder='big') + (len(json)).to_bytes(4, byteorder='big') + json
        #s.sendall(msg)


if __name__ == '__main__':
    main()
