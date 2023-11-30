#allows me to get song and artist of currently playing song without using API
#https://pypi.org/project/swspotify/
from SwSpotify import spotify

#pyautogui is for keyboard control
#time is for delay between things
#serial is to connect to arduino
import pyautogui, time, serial

#functions to control spotify
def skip():
    pyautogui.hotkey('command', 'right', interval=0.1)

def playPause():
    pyautogui.press('space')

def prev():
    pyautogui.hotkey('command', 'left', interval=0.1)

def openSpotify():
    pyautogui.hotkey('command', 'space', interval=0.1)

    pyautogui.write('Spotify', interval=0.1)

    pyautogui.press('enter')

# code to check which ports are active
# import serial.tools.list_ports

# ports = serial.tools.list_ports.comports()
# for port, desc, hwid in sorted(ports):
#     print(f"{port}: {desc} [hwid: {hwid}]")



# #code to print line from serial port
# import serial
# import time

# # Replace 'COM3' with your Arduino's serial port name
# ser = serial.Serial('/dev/cu.usbmodem101', 9600, timeout=1)
# time.sleep(2)  # wait for the serial connection to initialize

# while True:
#     if ser.in_waiting > 0:
#         line = ser.readline().decode('utf-8').rstrip()
#         print(line) 




if __name__ == '__main__' :

    arduinoName = "/dev/cu.usbmodem101"

    arduino = serial.Serial(port = arduinoName , baudrate = 9600) #Create Serial port object called arduino
    time.sleep(2) #wait for 2 seconds for the communication to get established

    #get currently playing song

    openSpotify()

    while True:

        # #get currently playing song
        # song = spotify.song()


        incoming = str(arduino.readline())

        if 'Play/Pause' in incoming:
            playPause()
            print("Paused")
        elif 'Skip' in incoming:
            skip()
            print("Skipped")
        elif 'Previous' in incoming:
            prev()
            print("Previous")
        
        incoming  = ""
