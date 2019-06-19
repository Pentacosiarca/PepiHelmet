class XYZcoord{
private:
    char valAH, valAL, valBH, valBL, valCH, valCL;
public:
    XYZcoord(int coorda[3]){
        i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
        i2c_write(0xA8);
        i2c_stop();

        i2c_rep_start((I2C_7BITADDR<<1)|I2C_READ);
        valAH = i2c_read(false);
        valAL = i2c_read(false);
        coorda[0] = valAL | valAH << 8; //values range from -8000 to +8000, for 360deg in this axis

        valBH = i2c_read(false);
        valBL = i2c_read(false);
        coorda[1] = valBL | valBH << 8; //values range from -8000 to +8000, for 360deg in this axis

        valCH = i2c_read(false);
        valCL = i2c_read(true);
        coorda[2] = valCL | valCH << 8; //values range from -8000 to +8000, for 360deg in this axis
    }
};

class POperation{
private:
    int* pointa[3];
    int* pointb[3];
public:
    POperation(int pointaa[3], int pointba[3]){
        (*pointa) = pointaa;
        (*pointb) = pointba;
    }

    int Module(){
        return sqrt(pow((pointb[0]-pointa[0]),2)+pow((pointb[1]-pointa[1]),2)+pow((pointb[2]-pointa[2]),2));
    }
};

class Sendcolour{

public:
    Sendcolour(int modulea, int pointaa[3], int pointba[3]){
        strip.Color(255,   0,   0);
        strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        //delay(wait);                           //  Pause for a moment
    }
};


