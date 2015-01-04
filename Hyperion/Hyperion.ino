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
static const uint8_t FADE_SPEED = 5;

static const int SERIAL_BAUD = 9600;

GU7000_Serial_Async interface(BAUD_RATE, SIN, BUSY, RESET); 
Noritake_VFD_GU7000 vfd;

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
  vfd.print("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}


// Cycle through a sequence that fades from one color to another
// Modified from https://learn.adafruit.com/rgb-led-strips/example-code
void color_fade() {
	int r, g, b;
	
	// fade from blue to violet
	for (b = 0; b < 256; b++) {
		analogWrite(BLUE, b);
		_delay_ms(FADE_SPEED);
	}
	// fade from blue to violet
	for (r = 0; r < 256; r++) {
		analogWrite(RED, r);
		_delay_ms(FADE_SPEED);
	}
	// fade from violet to red
	for (b = 255; b >= 0; b--) {
                analogWrite(BLUE, b);
		_delay_ms(FADE_SPEED);
	}
	// fade from red to yellow
	for (g = 0; g < 256; g++) {
		analogWrite(GREEN, g);
		_delay_ms(FADE_SPEED);
	}
	// fade from yellow to green
	for (r = 255; r >= 0; r--) {
		analogWrite(RED, r);
		_delay_ms(FADE_SPEED);
	}
	// fade from green to teal
	for (b = 0; b < 256; b++) {
		analogWrite(BLUE, b);
		_delay_ms(FADE_SPEED);
	}
	// fade from teal to blue
	for (g = 255; g >= 0; g--) {
		analogWrite(GREEN, g);
		_delay_ms(FADE_SPEED);
	}
	// fade out blue
	for (b = 255; b >= 0; b--) {
		analogWrite(BLUE, b);
		_delay_ms(FADE_SPEED);
	}
}

void loop() {

}
