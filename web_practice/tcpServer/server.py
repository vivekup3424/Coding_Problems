import socket

HOST = "127.0.0.1"
PORT = 8080
server_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(5)
print(f"Server is listening on {HOST}:{PORT}")
while True:
    client_socket, client_address = server_socket.accept()
    print(f"Connection accepted from {client_address}")
    data = client_socket.recv(1024).decode(encoding="utf-8")
    print(f"Received = {data}")

    response = "Hello from server"
    client_socket.send(response.encode(encoding="utf-8"))

    client_socket.close()
    print(f"Connection with {client_address} closed")
