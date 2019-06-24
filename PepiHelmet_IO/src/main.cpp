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
char time_d_ms = 10;

int* max_vals = NULL;
int* min_vals = NULL;

void setup(void) {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  #include <setupReg.h>
}

void loop(void){
  

  int* coord_a;
  int* coord_b;
  int* moduleAB;
  
  XYZcoord Coordinates_a;
  coord_a = Coordinates_a.ReturnVector();
  max_vals = Coordinates_a.ReturnMax();
  min_vals = Coordinates_a.ReturnMin();
  
  delay(time_d_ms);

  XYZcoord Coordinates_b;
  coord_b = Coordinates_b.ReturnVector();
  max_vals = Coordinates_b.ReturnMax();
  min_vals = Coordinates_b.ReturnMin();
  

  POperation Vecoperator(coord_a,coord_b);
  moduleAB = Vecoperator.Module();

  Sendcolour Sendcolour(moduleAB, coord_a, coord_b, max_vals, min_vals);
}