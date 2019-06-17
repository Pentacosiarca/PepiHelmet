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

void setup(void) {

  #include <setupReg.h>
}

void loop(void){

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0xA8);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_READ);
  byte valZH = i2c_read(false);
  byte valZL = i2c_read(false);
  int Zpos = valZL | valZH << 8;

  byte valYH = i2c_read(false);
  byte valYL = i2c_read(false);
  int Ypos = valYL | valYH << 8;

  byte valXH = i2c_read(false);
  byte valXL = i2c_read(true);
  int Xpos = valXL | valXH << 8; 

  delay(3000);
}