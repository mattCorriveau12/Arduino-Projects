// Written by Nick Gammon
// February 2011


#include <SPI.h>
#include <Wire.h>

char buf [100];
volatile byte pos;
volatile boolean process_it;

String message;
int count = 0;

/*-----------------------------------------------------------------*/

void setup (void)
{

/*----------------------------*/

  //SPI Setup

  Serial.begin (115200);   // debugging
  
  // turn on SPI in slave mode
  SPCR |= bit (SPE);

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPI.attachInterrupt();

/*----------------------------*/

  //I2C Setup

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event

}  // end of setup

/*-----------------------------------------------------------------*/


// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (process_it)
    {
    buf [pos] = 0;  
    Serial.println (buf);
    pos = 0;
    process_it = false;
    }  // end of flag set
    
}  // end of loop

/*-----------------------------------------------------------------*/

// SPI interrupt routine
ISR (SPI_STC_vect)
{
byte c = SPDR;  // grab byte from SPI Data Register
  
  // add to buffer if room
  if (pos < (sizeof (buf) - 1))
    buf [pos++] = c;
    
  // example: newline means time to process buffer
  if (c == '\n')
    process_it = true;
      
}  // end of interrupt routine SPI_STC_vect

//I2C Send Packet Routine

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
