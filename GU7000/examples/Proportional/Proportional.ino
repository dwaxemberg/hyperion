#include <GU7000_Interface.h>
#include <GU7000_Parallel.h>
#include <GU7000_Serial_Async.h>
#include <GU7000_Serial_Sync.h>
#include <Noritake_VFD_GU7000.h>

// ****************************************************
// ****************************************************
// Uncomment one of the communication interfaces below.
//
GU7000_Serial_Async interface(38400, 1, 23, 22); // BAUD RATE,SIN,BUSY,RESET
//GU7000_Serial_Sync interface(3, 5, 6, 7); // SIN,BUSY,SCK,RESET
//GU7000_Parallel interface('R', 8,9,10,11, 0,1,2,3,4,5,6,7); // Module Pin#3=RESET; BUSY,RESET,WR,RD,D0-D7
//GU7000_Parallel interface('B', 8,9,10,11, 0,1,2,3,4,5,6,7); // Module Pin#3=BUSY; BUSY,RESET,WR,RD,D0-D7
//GU7000_Parallel interface('N', 8,9,10,11, 0,1,2,3,4,5,6,7); // Module Pin#3=nothing; BUSY,RESET,WR,RD,D0-D7

//
// ****************************************************
// ****************************************************
Noritake_VFD_GU7000 vfd;

void setup() {
  _delay_ms(500);           // wait for device to power up
  vfd.begin(128, 32);       // 140x16 module
  // Enter the 4-digit model class number
  // E.g. 7040 for GU140X16G-7040A
  vfd.interface(interface); // select which interface to use
  vfd.isModelClass(7000);
  vfd.GU7000_reset();       // reset module
  vfd.GU7000_init();        // initialize module
  
  
  // Demonstrates the difference between fixed
  // and proportional fonts.
  vfd.GU7000_setFontStyle(false, false);
  vfd.println("fixed: lorem ipsum");
  vfd.GU7000_setFontStyle(true, false);
  vfd.print("propo: lorem ipsum");
}

void loop() {
}

