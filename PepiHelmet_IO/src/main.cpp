/*
 * Use of the library SoftI2CMaster (https://github.com/felias-fogg/SoftI2CMaster.git) 
 * to read accelerometer data from LIS3DH with the Attiny85.
 * Configuration registers in the LIS3DH follow the same sequence
 *  as in the accdemo example from Adafruit.
 */

#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#define LED_PIN   1
#define LED_COUNT 5
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


#define I2C_TIMEOUT 1000
#define I2C_PULLUP 1
#define SDA_PORT PORTB
#define SDA_PIN 0
#define SCL_PORT PORTB
#define SCL_PIN 2

#include <SoftI2CMaster.h>

#define I2C_7BITADDR (0x19) // with SDO --> Vcc
#define ADDRLEN 1        // address length, usually 1 or 2 bytes

int time_d_ms = 10;

const int averageCTE = 10;
const int dimensions = 3;

long coordArray[dimensions][averageCTE] = {NULL};
int count = 0;

long *ptrCoordArray = &coordArray[0][0];

long averageVal[dimensions] = {NULL};
long minVal[dimensions] = {NULL};
long maxVal[dimensions] = {NULL};

long *ptrAverage = &averageVal[0];
long *ptrMin = &minVal[0];
long *ptrMax = &maxVal[0];

int red,green,blue;

#include "tools.h"

void setup(void) {
 
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  #include "setupReg.h"

}

void loop(void){

// GET accel data and STORE
  long *ptrCoordCount = &coordArray[0][count];
  getXYZcoord(ptrCoordCount, ptrMax, ptrMin);
  
// COMPUTE from array
  computeFromXYZ(ptrCoordArray, ptrAverage, averageCTE, dimensions);

// DETERMINE rgb values
  performColour(ptrAverage, ptrMin, ptrMax, &red, &green, &blue, dimensions);
  
// SEND rgb to neopixel
  sendColour(red, green, blue);


  count++;
  if(count>averageCTE-1)count=0;

}
