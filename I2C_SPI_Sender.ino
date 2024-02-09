// I2C & SPI Master
// Requests an I2C Packet from the Slave and Sends a SPI Packet to the Slave
// Written by Matt Corriveau, February 2024
// Adapted from Nick Gammon, February 2011


#include <SPI.h>
#include <Wire.h>

int countSPI = 0;
char c;

/*---------------------------------------------------------------*/

void setup (void)
{
  //SPI Setup
  digitalWrite(SS, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  //I2C Setup
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  
}  // end of setup

/*---------------------------------------------------------------*/

void loop (void)
{

/*-----------------------*/

  //SPI Loop

  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10



//for (const char * p = "SPI Decode!\n" ; c = *p; p++)
    //SPI.transfer (c);

   if (countSPI==0) {
    SPImessage1();
    countSPI++;
    }

    else {
    SPImessage2();
    countSPI=0;
    }

  // disable Slave Select
  digitalWrite(SS, HIGH);

/*-------------------------*/

  //I2C Loop
  Wire.requestFrom(8, 12);    // request 6 bytes from peripheral device #8
  printPacket();
  Serial.println();


  delay (500);  // 1 seconds delay 
}  // end of loop

/*---------------------------------------------------------------*/

//Print SPI Packet

void SPImessage1() {
  // send test string
  for (const char * p = "Hello World!\n" ; c = *p; p++)
    SPI.transfer (c);
}

void SPImessage2() {
  // send test string
  for (const char * p = "SPI Decode!\n" ; c = *p; p++)
    SPI.transfer (c);

}

//Print I2C Packet

void printPacket() {
  while (Wire.available()) { // peripheral may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    
  }
}
