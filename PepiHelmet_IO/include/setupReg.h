
/*sequence of Registers manipulation from the accdemo example from Adafruit*/

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0x0F);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_READ);
  i2c_read(true);

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0x20);
  i2c_write(0x07);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0x20);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_READ);
  i2c_read(true);

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0x20);
  i2c_write(0x77);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0x23);
  i2c_write(0x88);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0x22);
  i2c_write(0x10);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0x1F);
  i2c_write(0x80);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0x23);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_READ);
  i2c_read(true);

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0x23);
  i2c_write(0x98);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
  i2c_write(0x23);
  i2c_stop();

  i2c_rep_start((I2C_7BITADDR<<1)|I2C_READ);
  i2c_read(true);