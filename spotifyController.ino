//importing lcd and remote libraries to use functions
#include <LiquidCrystal.h>
#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 2; // "Y" from IR Receiver connected to arduino pin 2


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup() {
  // code to enable the receiver that we created.
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");


  // // initializing the serial monitor.
  Serial.begin(9600);

  // // changing the serial's timing to wait for stream data to 0.
  // Serial.setTimeout(0);
}

void loop() {

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);

  //printing button pressed to serial monitor
  if (IrReceiver.decode()) {
    Serial.print("Command received: ");
    Serial.print(IrReceiver.decodedIRData.command);
    Serial.println();
    IrReceiver.resume();
  }
  
}
