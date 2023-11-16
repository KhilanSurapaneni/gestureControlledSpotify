#include <IRremote.hpp>
#define ENABLE_LED_FEEDBACK true

const int IR_RECEIVE_PIN = 7; // "Y" from IR Receiver connected to arduino pin 7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()) {
  Serial.print("Command received: ");
  Serial.print(IrReceiver.decodedIRData.command);
  Serial.println();
  IrReceiver.resume();
  }
  delay(1000);
}