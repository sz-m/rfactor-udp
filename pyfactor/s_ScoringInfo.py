import socket
import sys
from struct import *

s_ScoringInfo = {
		'mTrackName' 	: '',
		'mSession' 	: 0,
		'mNumVehicles' 	: 0,
		'mCurrentET'	: 0.0,
		'mEndET'	: 0.0,
		'mLapDist'	: 0.0
		} 

sc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

sc.bind(('0.0.0.0', 27015))
print('udp server ready')

while 1:
	data, addr = sc.recvfrom(512)
	unpacked_data = unpack('64s3l3f', data)
	
	s_ScoringInfo['mTrackName'] = unpacked_data[0].split(b'\x00')[0].decode()
	s_ScoringInfo['mSession'] = unpacked_data[1]
	s_ScoringInfo['mNumVehicles'] = unpacked_data[2]
	s_ScoringInfo['mCurrentET'] = unpacked_data[3]
	s_ScoringInfo['mEndET']	= unpacked_data[4]
	s_ScoringInfo['mLapDist'] = unpacked_data[5]

	out = 'mTrackName: {}\nmSession: {}, mNumVehicles: {}, mCurrentET: {}, mEndET: {}, mLapDist: {}'.format(s_ScoringInfo['mTrackName'], s_ScoringInfo['mSession'], s_ScoringInfo['mNumVehicles'], s_ScoringInfo['mCurrentET'], s_ScoringInfo['mEndET'], s_ScoringInfo['mLapDist'])

	print(out)
