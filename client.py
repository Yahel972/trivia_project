import socket
import json

HOST_IP = "127.0.0.1"  # The server's hostname or IP address
SERVER_PORT = 6969  # The port used by the server


def main():
    code = 2
    json = b'{username: "user1", password: "1234"}'
    msg = code.to_bytes(1, byteorder='big') + (len(json)).to_bytes(4, byteorder='big') + json

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST_IP, SERVER_PORT))
        s.sendall(msg)
        data = s.recv(1024)
        print(data.decode())


if __name__ == '__main__':
    main()
