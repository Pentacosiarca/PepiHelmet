void getXYZcoord(long *ptr2ArrayCoord, long *ptrMax, long *ptrMin){
  
  long valAH, valAL, valBH, valBL, valCH, valCL;
  
      i2c_rep_start((I2C_7BITADDR<<1)|I2C_WRITE);
      i2c_write(0xA8);
      i2c_stop();

      i2c_rep_start((I2C_7BITADDR<<1)|I2C_READ);
      valAH = i2c_read(false);
      valAL = i2c_read(false);
      *ptr2ArrayCoord = valAH | valAL<< 8;
      if (*ptr2ArrayCoord>*ptrMax) *ptrMax = *ptr2ArrayCoord;
      if (*ptr2ArrayCoord<*ptrMin) *ptrMin = *ptr2ArrayCoord;

      valBH = i2c_read(false);
      valBL = i2c_read(false);
      *(ptr2ArrayCoord+1) = valBH | valBL << 8; //values range from -8000 to +8000, for 360deg in this axis
      if (*(ptr2ArrayCoord+1)>*(ptrMax+1)) *(ptrMax+1) = *(ptr2ArrayCoord+1);
      if (*(ptr2ArrayCoord+1)<*(ptrMin+1)) *(ptrMin+1) = *(ptr2ArrayCoord+1);

      valCH = i2c_read(false);
      valCL = i2c_read(true);
      *(ptr2ArrayCoord+2) = valCH | valCL << 8; //values range from -8000 to +8000, for 360deg in this axis
      if (*(ptr2ArrayCoord+2)>*(ptrMax+2)) *(ptrMax+2) = *(ptr2ArrayCoord+2);
      if (*(ptr2ArrayCoord+2)<*(ptrMin+2)) *(ptrMin+2) = *(ptr2ArrayCoord+2);
}

void computeFromXYZ(long *ptrCoord, long *ptrAverage, const int averageCTE, const int dimensions){
  for (int i=0; i<dimensions ; i++){
      for (int j=0 ; j<averageCTE ; j++) *(ptrAverage+i)+= *(ptrCoord+j+i*averageCTE);
      *(ptrAverage+i)/=averageCTE;    
  }
}


void performColour(long *ptrAverage, long *ptrMin, long *ptrMax, int *ptrRed, int *ptrGreen, int *ptrBlue, const int dimensions){
  for(int i=0;i<dimensions;i++){
    //long avVal = (abs(minVal[0])+maxVal[0])/2;
    *(ptrAverage+i)+=abs(*(ptrMin+i));
    //*(ptrMin+i)+=abs(*(ptrMin+i));
    *(ptrMax+i)+=abs(*(ptrMin+i));

    if(*(ptrAverage+i)>*(ptrMax+i))*(ptrAverage+i)=*(ptrMax+i);
    if(*(ptrAverage+i)<0)*(ptrAverage+i)=0;
    }
  /*
  *ptrRed = map(*(ptrAverage+0),*(ptrMin+0),*(ptrMax+0),0,255);
  *ptrGreen = map(*(ptrAverage+1),*(ptrMin+1),*(ptrMax+1),0,255);
  *ptrBlue = map(*(ptrAverage+2),*(ptrMin+2),*(ptrMax+2),0,255);
*/
  *ptrRed = map(*(ptrAverage+0),0,*(ptrMax+0),0,255);
  *ptrGreen = map(*(ptrAverage+1),0,*(ptrMax+1),0,255);
  *ptrBlue = map(*(ptrAverage+2),0,*(ptrMax+2),0,255);
}

void sendColour(int red, int green, int blue){
  for(int i=0;i<LED_COUNT;i++){
      strip.setPixelColor(i, strip.Color(red, green, blue));         //  Set pixel's color (in RAM)
      strip.show();                          //  Update strip to match
      delay(10);                           //  Pause for a moment
  }
}
