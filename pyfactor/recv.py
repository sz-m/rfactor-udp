import socket
import sys

sc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sc.bind(('0.0.0.0', 27015))

while 1:
	data, addr = sc.recvfrom(1024)
	print('%r > %r'%(data, addr))
