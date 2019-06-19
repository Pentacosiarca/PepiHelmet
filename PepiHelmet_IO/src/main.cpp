/*
 * Use of the library SoftI2CMaster (https://github.com/felias-fogg/SoftI2CMaster.git) 
 * to read accelerometer data from LIS3DH with the Attiny85.
 * Configuration registers in the LIS3DH follow the same sequence
 *  as in the accdemo example from Adafruit.
 */

#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#define LED_PIN   3
#define LED_COUNT 2
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
int coord_a[3];
int coord_b[3];
char time_d_ms = 10;

void setup(void) {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  #include <setupReg.h>
}

void loop(void){
  XYZcoord coordinates_a(coord_a);
  delay(time_d_ms);
  XYZcoord coordinates_b(coord_b);

  POperation vecoperator(coord_a,coord_b);
  int moduleAB = vecoperator.Module();

  
  
}