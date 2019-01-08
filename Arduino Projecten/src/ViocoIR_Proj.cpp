#include <Arduino.h>
// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
#include <AFMotor.h> //DO NOT forget to include this library by "Sketch->Include Library->Add ZIP library
#include <IRremote.h>
#include <IRremoteInt.h>

int RECV_PIN = 11;          //  The digital pin that the signal pin of the sensor is connected to
IRrecv irrecv (RECV_PIN);  //  Create a new receiver object that would decode signals to key codes
decode_results results;     //  A varuable that would be used by receiver to put the key code into

AF_DCMotor motor1(1);
AF_DCMotor motor2(4);


void setup() { 
 irrecv.enableIRIn();    //  Enable receiver so that it would start processing infrared signals
    
 Serial.begin(9600); // set up Serial library at 9600 bps
 Serial.println("Motor test!");
 // turn on motor
 
 motor1.setSpeed(200);
 motor1.run(RELEASE);
 motor2.setSpeed(200);
 motor2.run(RELEASE);
}


void loop() {


  if (irrecv.decode(&results)) {            //  Decode the button code and put it in "results" variable
     Serial.println("signal received");
     Serial.println(results.value, HEX);       //  Print the code as a hexadecimal value

    if (results.value == 0xD7E84B1B) {          //  Key '1' is pressed which belongs to the blue LED
       Serial.println("+");

       motor1.run(BACKWARD);
       motor2.run(BACKWARD);

       for (int i=0; i < 255; i++) {
        motor1.setSpeed(i);
        motor2.setSpeed(i);
        delay(10);
       }

       for (int i=255; i > 0; i--) {
        motor1.setSpeed(i);
        motor2.setSpeed(i);
        delay(10);
       }
 
    }
    irrecv.resume();                        //  Continue listening for new signals

  }   
} 