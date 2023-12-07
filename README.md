# gestureControlledSpotify

We created a device that can control Spotify on the laptop. Hand gestures captured by ultrasonic sensors or a remote control can: pause, play, skip, or go back. The current song is displayed on an LCD screen. An Arduino Uno processes inputs from the sensors and controls the LCD screen. A Python script takes information from the Arduino to interact with Spotify on the computer. All materials used came from the Arduino Kit provided by Northrop Grumman.

**What it does**: 
Controls Spotify through hand gestures and a remote. The LCD shows the user the action of the gesture.

**How it works**: 
We interact with Spotify by using a Python script that is used to control the app through the keyboard. Ultrasonic sensors detect when your hands are completing a gesture. IR receiver receives inputs from a remote control.

**Issues We Ran Into**:
The Spotify API is able to grab the exact song and artist that is selected. However becuase the Arduino Uno only has one serial port we were not able to use the serial to send the data from the Spotify API to the Arduino as the python program containing the Spotify API was already using the serial port to read data from the Arduino. If we had an extra serial port on the Arduino we could have made this possible

**Video Displaying Project and its Functionality**: https://drive.google.com/file/d/11rgGOZ1zAXE-O9sFJ-f7ZoNeh6S5twvG/view?usp=share_link

