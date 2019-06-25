/*
 * Use of the library SoftI2CMaster (https://github.com/felias-fogg/SoftI2CMaster.git) 
 * to read accelerometer data from LIS3DH with the Attiny85.
 * Configuration registers in the LIS3DH follow the same sequence
 *  as in the accdemo example from Adafruit.
 */

#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#define LED_PIN   1
#define LED_COUNT 1
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

#include <tools.h>
int time_d_ms = 10;

const int averageCTE = 10;
const int dimensions = 3;
int count = 0;

int* max_vals = NULL;
int* min_vals = NULL;

int* coordArray = create2Darray(dimensions, averageCTE);

void setup(void) {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  #include <setupReg.h>

}

void loop(void){
  
  int* moduleAB;
  
  //delay(time_d_ms);

  XYZcoord Coordinates_b;
  Coordinates_b.ReturnVector(coordArray,dimensions,count);
  max_vals = Coordinates_b.ReturnMax();
  min_vals = Coordinates_b.ReturnMin();
  
  count += 1;
  if (count > 10){
    count = 0;

    POperation Vecoperator(coordArray,dimensions,count);
    moduleAB = Vecoperator.Module();

    Sendcolour Sendcolour(coordArray, max_vals, min_vals, moduleAB, dimensions, averageCTE);
  }
}