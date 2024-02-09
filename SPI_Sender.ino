// Written by Nick Gammon
// February 2011


#include <SPI.h>

int countSPI = 0;
char c;

void setup (void)
{

  digitalWrite(SS, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  // end of setup


void loop (void)
{

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

  delay (500);  // 1 seconds delay 
}  // end of loop

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
