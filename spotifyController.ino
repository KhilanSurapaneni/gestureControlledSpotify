/*
 * gesture control program for controlling certain functions in windows pc
 * Code by BalaAppu
 * Website: www.electronicshub.org
 */
#include <LiquidCrystal.h>
#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 2;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int trigPin1 = 6; // the number of the trigger output pin ( sensor 1 )
const int echoPin1 = 5; // the number of the echo input pin ( sensor 1 )     
const int trigPin2 = 4;  // the number of the trigger output pin ( sensor 2 ) 
const int echoPin2 = 3;  // the number of the echo input pin ( sensor 2 ) 

////////////////////////////////// variables used for distance calculation 
long duration;                               
int distance1, distance2; 
float r;
unsigned long temp=0;
int temp1=0;
int l=0;
////////////////////////////////

void find_distance (void);

// this function returns the value in cm.
/*we should not trigger the both ultrasonic sensor at the same time. 
it might cause error result due to the intraction of the both soundswaves.*/ 
void find_distance (void)                   
{ 
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);

    duration = pulseIn(echoPin1, HIGH, 5000);// here this pulsein function wont wait more then 5000us for the ultrasonic sound to came back. (due to this it wont measure more than 60cm)
                                            // it helps this project to use the gesture control in the defined space. 
                                            // so that, it will return zero if distance greater then 60m. ( it helps usually if we remove our hands infront of the sensors ).
  
    r = 3.4 * duration / 2;                  // calculation to get the measurement in cm using the time returned by the pulsein function.     
    distance1 = r / 100.00;
    /////////////////////////////////////////upper part for left sensor and lower part for right sensor
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);

    duration = pulseIn(echoPin2, HIGH, 5000);
    r = 3.4 * duration / 2;     
    distance2 = r / 100.00;
    delay(100);
  }

  void setup() 
  {
    Serial.begin(9600);
    pinMode(trigPin1, OUTPUT); // initialize the trigger and echo pins of both the sensor as input and output:
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    delay (1000);

    //code to intialize IR Receiver for Remote
    IrReceiver.begin(IR_RECEIVE_PIN);

    // put your setup code here, to run once:
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);    
}

void loop()
{
    String x;
    find_distance(); // this function will stores the current distance measured by the ultrasonic sensor in the global variable "distance1 and distance2"
                    // no matter what, the program has to call this "find_distance" function continuously to get the distance value at all time.
    
    

    //printing button pressed to serial monitor
    int buttonPress = 0;

    if (IrReceiver.decode()) {
      buttonPress = IrReceiver.decodedIRData.command;
      IrReceiver.resume();
    }


    //if a hand is in front of the right sensor between 5 and 25 cm and there is no hand in front of the left sensor or
    //whether skip button is pressed on remote
    //Skip will be printed
    if ((distance2 >= 5 && distance2 <= 25 && distance1 == 0) || buttonPress == 67){
      Serial.println("Skip");
      x = "Skip";
    }
    
    //if a hand is in front of the left sensor between 5 and 25 cm and there is no hand in front of the right sensor or previous button is pressed
    //Rewind will be printed
    if ((distance1 >= 5 && distance1 <= 25 && distance2 == 0) || buttonPress == 68)
    {
      Serial.println("Previous");
      x = "Previous";
    }

    //if a hand is in front of the left sensor between 5 and 25 cm and a hand is in front of the right sensor between 5 and 25 cm.
    //or pause button is pressed
    if ((distance1 >= 5 && distance1 <= 25 && distance2 >= 5 && distance2 <= 25) || buttonPress == 64)
    {
      Serial.println("Play/Pause");
      x = "Play/Pause";
    }


    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    
    //displaying function to LCD Display
    lcd.print(x);

    delay(500);
 
    lcd.clear();

    buttonPress = 0;

    x = "";

    delay(250);
    
}





