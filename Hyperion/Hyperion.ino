#include <GU7000_Interface.h>
#include <GU7000_Serial_Async.h>
#include <Noritake_VFD_GU7000.h>

// VFD constants
static const long BAUD_RATE = 38400;
static const uint8_t SIN = 1;
static const uint8_t BUSY = 23;
static const uint8_t RESET = 22;

// LED constants
static const uint8_t RED = 10;
static const uint8_t GREEN = 9;
static const uint8_t BLUE = 11;

static const int SERIAL_BAUD = 9600;

GU7000_Serial_Async interface(BAUD_RATE, SIN, BUSY, RESET); 
Noritake_VFD_GU7000 vfd;

uint8_t tick;
uint8_t color;

void setup() {
  // Setup the VFD
  _delay_ms(500);           // wait for vfd to power up
  vfd.begin(128, 32);       // 128x32 module
  vfd.interface(interface);
  vfd.isModelClass(7000);
 
  vfd.GU7000_reset();  // reset vfd module
  vfd.GU7000_init();   // initialize vfd module
  
  // Initialize the LEDs to off
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  
  Serial.begin(SERIAL_BAUD);
  
  vfd.GU7000_clearScreen();
  vfd.GU7000_setFontStyle(true, false);
  vfd.GU7000_setScrollMode(HorizScrollMode);
  vfd.GU7000_setHorizScrollSpeed(3);
}

// Cycle through a sequence that fades from one color to another
// Modified from https://learn.adafruit.com/rgb-led-strips/example-code
void color_fade(uint8_t tick) {
  switch(color) {
    case 0:
      analogWrite(BLUE, tick);
      break;
    case 1:
      analogWrite(RED, tick);
      break;
    case 2:
      analogWrite(GREEN, tick);
      break;
    case 3:
      analogWrite(BLUE, 255 - tick);
      break;
    case 4:
      analogWrite(RED, 255 - tick);
      break;
    case 5:
      analogWrite(GREEN, 255 - tick);
      break;
  }
  if (tick == 255) {
    color = color >= 5 ? 0 : color + 1;
  }
}

void printStep(const char* str, uint8_t tick) {
  size_t len = strlen(str);
  uint8_t gap = 255 / (len - 1);
  if (tick % gap == 0) {
    vfd.print(str[tick / gap]);
  }
}

void loop() {
  printStep("Hackers Gonna Hack    ", tick);
  color_fade(tick++);
  _delay_ms(5);
}
