# Echo server program
import socket

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 6790               # Arbitrary non-privileged port
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(1)
    conn, addr = s.accept()
    with conn:
        print('Connected by', conn, addr)
        while True:
            data = conn.recv(1024)
            if not data: break
            print('Received ', data)
            conn.sendall(data) 