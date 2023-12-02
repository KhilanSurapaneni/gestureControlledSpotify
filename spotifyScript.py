#allows me to get song and artist of currently playing song without using API
#https://pypi.org/project/swspotify/
from SwSpotify import spotify

#pyautogui is for keyboard control
#time is for delay between things
#serial is to connect to arduino
import pyautogui, time, serial

#spotifyAPI to get currently playing song
import spotipy
from spotipy.oauth2 import SpotifyOAuth

# Set up your Spotify credentials
client_id = 'be993bd5270340218be21d86d9e0361d'
client_secret = 'beeaf5111ddf498fa7c52493e69b3799'
redirect_uri = 'http://localhost:8080/callback'
scope = 'user-read-currently-playing'

# Authorization
auth_manager = SpotifyOAuth(client_id, client_secret, redirect_uri, scope=scope)
sp = spotipy.Spotify(auth_manager=auth_manager)


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

#function to get song from Spotify using API
def getSong():
    # Getting the current song
    current_track = sp.current_user_playing_track()
    if current_track is not None:
        track_name = current_track['item']['name']
        artist_name = current_track['item']['artists'][0]['name']
    else:
        recently_played = sp.current_user_recently_played(limit=1)
        if recently_played['items']:
            last_track = recently_played['items'][0]['track']
            track_name = last_track['name']
            artist_name = last_track['artists'][0]['name']
        else:
            track_name = ""
            artist_name = ""
    
    return [track_name, artist_name]

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

        #get currently selected song details
        details = getSong()

        #sort into song and artist
        song = details[0]
        artist = details[1]


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
