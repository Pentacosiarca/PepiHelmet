class XYZcoord{
private:
    char valAH, valAL, valBH, valBL, valCH, valCL;
public:
    XYZcoord(int& Aa,int& Ba,int& Ca){
        i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
        i2c_write(0xA8);
        i2c_stop();

        i2c_rep_start((I2C_7BITADDR<<1)|I2C_READ);
        valAH = i2c_read(false);
        valAL = i2c_read(false);
        Aa = valAL | valAH << 8; //values range from -8000 to +8000, for 360deg in this axis

        valBH = i2c_read(false);
        valBL = i2c_read(false);
        Ba = valBL | valBH << 8; //values range from -8000 to +8000, for 360deg in this axis

        valCH = i2c_read(false);
        valCL = i2c_read(true);
        Ca = valCL | valCH << 8; //values range from -8000 to +8000, for 360deg in this axis
    }
};