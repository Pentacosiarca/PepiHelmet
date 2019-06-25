class XYZcoord{
private:
    int valAH, valAL, valBH, valBL, valCH, valCL;
    int* coorda = new int[3];
    int* maxval = new int[3];
    int* minval = new int[3];
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

    ~XYZcoord(){
        delete[] coorda;
        delete[] maxval;
        delete[] minval;
    }

    void ReturnVector(int* arr,const int& rows, int& count){
        for(int i=0;i<rows;i++)
            arr[i+rows*count] = coorda[i];
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
    int* arr_a;
    int* arr_b;

public:
    POperation(int* arra, const int& dimensions, int& count){
        arr_a = new int[dimensions];
        for(int i=0;i<dimensions;i++)
            arr_a[i] = arra[i + (dimensions*count)];
    }

    ~POperation(){
        delete[] arr_a;
        delete[] arr_b;
    }

    int* Module(){
        return arr_a; //sqrt(pow((pointb[0]-pointa[0]),2)+pow((pointb[1]-pointa[1]),2)+pow((pointb[2]-pointa[2]),2));
    }
};

class Sendcolour{
private:
    int dim;
    int aveCTE;
    int* arr_a;
    int* maxval = new int[3];
    int* minval = new int[3];
    int* module = new int[3];
    int* averageArr = new int[3];
    int red;
    int green;
    int blue;

public:
    Sendcolour(int* arraa, int* maxvala, int* minvala, int* modulea, const int dimensionsa, const int averageCTEa){
        dim = dimensionsa;
        aveCTE = averageCTEa;

        arr_a = new int[dim * aveCTE];
        for(int i=0;i<dim;i++){
            for(int j=0;j<aveCTE;j++)
                arr_a[ + i + (dim*j)] = arraa[i + (dim*j)];
            maxval[i] = maxvala[i];
            minval[i] = minvala[i];
            module[i] = modulea[i];
        }
        AverageArr();
        PerformColour();
        Colour();
    }

    ~Sendcolour(){
        delete[] maxval;
        delete[] minval;
        delete[] module;
        delete[] averageArr;
        delete[] arr_a;
    }

private:
    void AverageArr(){
        for(int i=0;i<dim;i++){
            for(int j=0;j<aveCTE;j++)
                averageArr[i] += arr_a[i + (dim*j)]/aveCTE;
        }
    }

    void PerformColour(){
        red = map(averageArr[1],minval[1],maxval[1],0,255);
        green = 10; //map(averageArr[1],minval[1],maxval[1],0,255);
        blue = 10; //map(averageArr[2],minval[2],maxval[2],0,255);
    }

    void Colour(){
        for(int i=0;i<LED_COUNT;i++)
            strip.setPixelColor(i, strip.Color(red, green, blue));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
        //delay(wait);           ,                //  Pause for a moment
    }
};

int* create2Darray(int rows, int columns) {
	int* array2D = NULL;
	array2D = new int [rows * columns];
	return array2D;
}


