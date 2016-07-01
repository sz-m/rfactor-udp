import socket
import sys
from struct import *
import rpm
import hd44780

s_TelemInfo = {
		'mVehicleName'		: '',
		'mTrackName' 		: '',
		'mLapNumber'		: 0,
		'mGear'				: 0,
		'mDeltaTime'		: 0.0,
		'mLapStartET'		: 0.0,
		'mEngineRPM'		: 0.0,
		'mEngineWaterTemp'	: 0.0,
		'mEngineOilTemp'	: 0.0,
		'mClutchRPM'		: 0.0,
		'mUnfilteredThrottle'	: 0.0,
		'mUnfilteredBrake'	: 0.0,
		'mUnfilteredSteering'	: 0.0,
		'mUnfilteredClutch'	: 0.0,
		'mSteeringArmForce'	: 0.0,
		'mVelocity'		: 0.0
		} 

sc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

sc.bind(('0.0.0.0', 27015))
print('udp server ready')

lcd = hd44780.HD44780()
lcd.message('.ready()')

while 1:
	data, addr = sc.recvfrom(512)
	unpacked_data = unpack('64s64s2l12f', data)

	s_TelemInfo['mVehicleName'] = unpacked_data[0].split(b'\x00')[0].decode()
	s_TelemInfo['mTrackName'] = unpacked_data[1].split(b'\x00')[0].decode()
	s_TelemInfo['mLapNumber'] = unpacked_data[2]
	s_TelemInfo['mGear'] = unpacked_data[3]
	s_TelemInfo['mDeltaTime'] = unpacked_data[4]
	s_TelemInfo['mLapStartET'] = unpacked_data[5]
	s_TelemInfo['mEngineRPM'] = unpacked_data[6]
	s_TelemInfo['mEngineWaterTemp'] = unpacked_data[7]
	s_TelemInfo['mEngineOilTemp'] = unpacked_data[8]
	s_TelemInfo['mClutchRPM'] = unpacked_data[9]
	s_TelemInfo['mUnfilteredThrottle'] = unpacked_data[10]
	s_TelemInfo['mUnfilteredBrake'] = unpacked_data[11]
	s_TelemInfo['mUnfilteredSteering'] = unpacked_data[12]
	s_TelemInfo['mUnfilteredClutch'] = unpacked_data[13]
	s_TelemInfo['mSteeringArmForce'] = unpacked_data[14]
	s_TelemInfo['mVelocity'] = unpacked_data[15]

	lcd_string = '{3:16s}\n{0:1d}    {1:4.0f}    {2:3.0f}'.format(
								s_TelemInfo['mGear'],
								s_TelemInfo['mEngineRPM'],
								s_TelemInfo['mVelocity'],
								rpm.rpm(s_TelemInfo['mEngineRPM'])
								)

	lcd.message(lcd_string)
	lcd.cmd(0x2)
	print(lcd_string)
