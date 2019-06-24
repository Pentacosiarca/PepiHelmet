class XYZcoord{
private:
    char valAH, valAL, valBH, valBL, valCH, valCL;
    int coorda[3];
    int maxval[3];
    int minval[3];
public:
    XYZcoord(){
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

    int* ReturnVector(){
        return coorda;
    }
    int* ReturnMax(){
        if(coorda[0]>maxval[0])
            maxval[0]=coorda[0];
        if(coorda[1]>maxval[1])
            maxval[1]=coorda[1];
        if(coorda[2]>maxval[2])
            maxval[2]=coorda[2];
        return maxval;
    }

    int* ReturnMin(){
        if(coorda[0]<minval[0])
            minval[0]=coorda[0];
        if(coorda[1]<minval[1])
            minval[1]=coorda[1];
        if(coorda[2]<minval[2])
            minval[2]=coorda[2];
        return minval;
    }
};

class POperation{
private:
    int pointa[3];
    int pointb[3];

public:
    POperation(int* pointaa, int* pointba){
        for(int i=0;i<3;i++){
            pointa[i] = pointaa[i]; //sqrt(pow((pointaa[i] - pointba[i]),2));
            //pointb[i] = pointba[i];
        }
    }

    int* Module(){
        return pointa; //sqrt(pow((pointb[0]-pointa[0]),2)+pow((pointb[1]-pointa[1]),2)+pow((pointb[2]-pointa[2]),2));
    }
};

class Sendcolour{
private:
    int pointa[3];
    int pointb[3];
    int maxval[3];
    int minval[3];
    int module[3];
    char red;
    char green;
    char blue;

public:
    Sendcolour(int* modulea, int* pointaa, int* pointba, int* maxvala, int* minvala){
        for(int i=0;i<3;i++){
            pointa[i] = pointaa[i];
            pointb[i] = pointba[i];
            maxval[i] = maxvala[i];
            minval[i] = minvala[i];
            module[i] = modulea[i];
        }
        //module = modulea;
        PerformColour();
        Colour();
    }

private:
    void PerformColour(){
        red = map(module[0],minval[0],maxval[0],0,255);
        green = map(module[1],minval[1],maxval[1],0,255);
        blue = map(module[2],minval[2],maxval[2],0,255);
    }

    void Colour(){
        for(int i=0;i<LED_COUNT;i++)
            strip.setPixelColor(i, strip.Color(red, green, blue));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        //delay(wait);           ,                //  Pause for a moment
    }
};


