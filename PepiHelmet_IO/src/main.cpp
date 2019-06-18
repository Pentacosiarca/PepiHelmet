/*
 * Use of the library SoftI2CMaster (https://github.com/felias-fogg/SoftI2CMaster.git) 
 * to control the accelerometer LIS3DH with the Attiny85.
 * Configuration bits follow the same pattern as in the accdemo example from Adafruit.
 */

#include <Arduino.h>

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
int Xcoord_a, Ycoord_a, Zcoord_a;
int Xcoord_b, Ycoord_b, Zcoord_b;
char time_d_ms = 10;

void setup(void) {
  #include <setupReg.h>
}

void loop(void){
  XYZcoord coordinates_a(Xcoord_a, Ycoord_a, Zcoord_a);
  delay(time_d_ms);
  XYZcoord coordinates_b(Xcoord_b, Ycoord_b, Zcoord_b);


}