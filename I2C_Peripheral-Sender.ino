// Wire Peripheral Sender
// By Matt Corriveau
// Adapted from Nicholas Zambetti [http://www.zambetti.com](http://www.zambetti.com)

// Demonstrates use of the Wire library
// Sends message1 upon request, then sends the message2 upon request
// Sends data as an I2C/TWI peripheral device
// Refer to the "Wire Master Reader" example for use with this

// Modified 8 February 2024
// Originally created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

String message;
int count = 0;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  
}

void loop() {
  delay(100);
  
}


// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
    
    //counter determines whether message1 or message 2 will be sent, then
    //counter increments so the other message can be sent on the next request
    if (count==0) {
    message1();
    count++;
    }

    else {
    message2();
    count=0;
    }
  
}

void message1() {
  Wire.write("Hello World!"); // respond with message of 12 bytes
  // as expected by master
}

void message2() {
  Wire.write("I2C Decode! "); // respond with message of 12 bytes
  // as expected by master
}
