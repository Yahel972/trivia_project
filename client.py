import socket

HOST_IP = "127.0.0.1"  # The server's hostname or IP address
SERVER_PORT = 6969  # The port used by the server
CHECK_MSG = b"Hello"


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST_IP, SERVER_PORT))
        data = s.recv(1024)
        print(data.decode())
        s.sendall(CHECK_MSG)


if __name__ == '__main__':
    main()
