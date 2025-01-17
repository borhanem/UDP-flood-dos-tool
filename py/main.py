import socket
import time
from socket import error as SocketError
import errno

HOST = "10.255.255.255"
PORT = 8080
CHUNK_SIZE = 1024
MESSAGE = b"FLOOD!"

try:
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP) as sock:
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        sock.settimeout(1)
        # Send 10 udp ping messages
        rtt_times = []
        data_buf = None
        while True:
            try:
                sock.sendto(MESSAGE, (HOST, PORT))
            except TimeoutError:
                print("Request timed out.")
except SocketError as e:
    if e.errno == errno.ECONNRESET:
        print("OOPS!")
        exit(-1)
    else:
        raise
