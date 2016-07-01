import socket
import sys
import hd44780

try:
	sc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

except socket.error:
	print("Failed to create socket.")
	sys.exit()

host = '192.168.0.36'
port = 27015
lcd = hd44780.HD44780()

addr = host, port

sc.sendto(bytes('start()', 'ascii'),addr)
lcd.message('.start()')

while(1):
	try:
		d = sc.recvfrom(512)
		reply = d[0]
		addr = d[1]
		#print(str(addr) + ' > ' + str(reply))
		lcd.message('{}\n{}'.format(str(addr), str(reply)))

	except socket.error as e:
		print(str(e))
		sys.exit()

	except KeyboardInterrupt:
		break

sc.sendto(bytes('stop()', 'ascii'),addr)
print('Completed.')
