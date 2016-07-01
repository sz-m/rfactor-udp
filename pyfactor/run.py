import socket
import struct
import sys
import time
import threading

import hd44780
import s_struct
import rpm
from string_shift import *

lcd = hd44780.HD44780()
lcd.message('.ready()')

# push button
button_value = 0
hd44780.GPIO.setup(27, hd44780.GPIO.IN)

def lcd_clean():
    lcd.message('{}\n{}'.format(' '*16, ' '*16))
    lcd.cmd(0x2)

#################################################################
#################################################################
#################################################################
class pushbuttonThread(threading.Thread):
    def __init__(self, threadID, name):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.button_value = 0

    def run(self):
        while 1:
            if(hd44780.GPIO.input(27)==False):
                self.button_value = (self.button_value +1)%7
                time.sleep(0.2)

    def get(self):
        return self.button_value

#################################################################
#################################################################
#################################################################
class telemetryThread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.sc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sc.bind(('0.0.0.0', 27015))

    def run(self):
        while 1:
            self.data, self.addr = self.sc.recvfrom(512)
            self.unpacked_data = struct.unpack('64s64s2l12f', self.data)

            s_struct.s_TelemInfo['mVehicleName'] = self.unpacked_data[0].split(b'\x00')[0].decode()
            s_struct.s_TelemInfo['mTrackName'] = self.unpacked_data[1].split(b'\x00')[0].decode()
            s_struct.s_TelemInfo['mLapNumber'] = self.unpacked_data[2]
            s_struct.s_TelemInfo['mGear'] = self.unpacked_data[3]
            s_struct.s_TelemInfo['mDeltaTime'] = self.unpacked_data[4]
            s_struct.s_TelemInfo['mLapStartET'] = self.unpacked_data[5]
            s_struct.s_TelemInfo['mEngineRPM'] = self.unpacked_data[6]
            s_struct.s_TelemInfo['mEngineWaterTemp'] = self.unpacked_data[7]
            s_struct.s_TelemInfo['mEngineOilTemp'] = self.unpacked_data[8]
            s_struct.s_TelemInfo['mClutchRPM'] = self.unpacked_data[9]
            s_struct.s_TelemInfo['mUnfilteredThrottle'] = self.unpacked_data[10]
            s_struct.s_TelemInfo['mUnfilteredBrake'] = self.unpacked_data[11]
            s_struct.s_TelemInfo['mUnfilteredSteering'] = self.unpacked_data[12]
            s_struct.s_TelemInfo['mUnfilteredClutch'] = self.unpacked_data[13]
            s_struct.s_TelemInfo['mSteeringArmForce'] = self.unpacked_data[14]
            s_struct.s_TelemInfo['mVelocity'] = self.unpacked_data[15]

#################################################################
#################################################################
#################################################################
class scoringThread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.sc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sc.bind(('0.0.0.0', 27016))

    def run(self):
        while 1:
            self.data, self.addr = self.sc.recvfrom(512)
            self.unpacked_data = struct.unpack('64s3l3f', self.data)

            s_struct.s_ScoringInfo['mTrackName'] = self.unpacked_data[0].split(b'\x00')[0].decode()
            s_struct.s_ScoringInfo['mSession'] = self.unpacked_data[1]
            s_struct.s_ScoringInfo['mNumVehicles'] = self.unpacked_data[2]
            s_struct.s_ScoringInfo['mCurrentET'] = self.unpacked_data[3]
            s_struct.s_ScoringInfo['mEndET']	= self.unpacked_data[4]
            s_struct.s_ScoringInfo['mLapDist'] = self.unpacked_data[5]


pbThread = pushbuttonThread(1, "pushbutton")
pbThread.start()

telThread = telemetryThread()
telThread.start()

scThread = scoringThread()
scThread.start()

while 1:
    if(button_value is not pbThread.get()):
        button_value = pbThread.get()
        lcd_clean()

    if(button_value == 0):
        #E0
        a = '    {0:8s}    '.format(time.strftime("%H:%M:%S", time.gmtime()))
        b = '{}'.format(time.strftime("%a, %d %b %Y", time.gmtime()))
        lcd_string = '{}\n{}'.format(a,b)

    elif(button_value == 1):
        #E1
        lcd_string = '{3:16s}\n{0:1d}    {1:4.0f}    {2:3.0f}'.format(
								s_struct.s_TelemInfo['mGear'],
								s_struct.s_TelemInfo['mEngineRPM'],
								s_struct.s_TelemInfo['mVelocity'],
								rpm.rpm(s_struct.s_TelemInfo['mEngineRPM'])
        )

    elif(button_value == 2):
        #E4
        lcd_string = 'T {0:2.3f} B {1:2.3f}\nS {2:2.3f} C {3:2.3f}'.format(
                                s_struct.s_TelemInfo['mUnfilteredThrottle'],
                                s_struct.s_TelemInfo['mUnfilteredBrake'],
                                s_struct.s_TelemInfo['mUnfilteredSteering'],
                                s_struct.s_TelemInfo['mUnfilteredClutch']
        )


    elif(button_value == 3):
        lcd_string = '{0:16s}\n{1:16s}'.format(
                               string_shift(s_struct.s_TelemInfo['mVehicleName']),
                               string_shift(s_struct.s_TelemInfo['mTrackName'])
        )

    elif(button_value == 4):
        lcd_string = 'Oil:       {0:2.2f}\nWater:     {1:2.2f}'.format(
                                s_struct.s_TelemInfo['mEngineWaterTemp'],
                                s_struct.s_TelemInfo['mEngineOilTemp']
        )

    elif(button_value == 5):
        lcd_string = 'Session:       {0:d}\nVehicles:     {1:2d}'.format(
                                s_struct.s_ScoringInfo['mSession'],
                                s_struct.s_ScoringInfo['mNumVehicles']
        )

    elif(button_value == 6):
        lcd_string = 'CT: {0:11.1f}\nET: {1:11.1f}'.format(
                                s_struct.s_ScoringInfo['mCurrentET'],
                                s_struct.s_ScoringInfo['mNumVehicles']
        )



    lcd.message(lcd_string)
    lcd.cmd(0x2)




