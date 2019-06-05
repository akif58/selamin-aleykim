

#include "SparkFun_Tlc5940.h"
#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68
byte decToBcd(byte val)
{
return( (val/10 * 16) + (val%10) );
}
byte bcdToDec(byte val)
{
return( (val/16 * 10) + (val%16) );
}
byte saniye[60]={15,12,9,6,3,0,29,26,23,20,17,46,43,40,37,32,63,60,57,54,51,48,77,74,71,68,65,94,91,88,85,82,111,108,105,102,99,96,125,122,119,116,113,142,139,136,133,130,159,156,153,150,147,144,173,170,167,164,161,190};
byte dakika[60]={14,11,8,5,2,31,28,25,22,19,16,45,42,39,36,33,62,59,56,53,50,79,76,73,70,67,64,93,90,87,84,81,110,107,104,101,98,127,124,121,118,115,112,141,138,135,132,129,158,155,152,149,146,175,172,169,166,163,160,189};
byte saat[60]= {13,10,7,4,1,30,27,24,21,18,47,44,41,38,35,34,61,58,55,52,49,78,75,72,69,66,95,92,89,86,83,80,109,106,103,100,97,126,123,120,117,114,143,140,137,134,131,128,157,154,151,148,145,174,171,168,165,162,191,188}; 
byte E1[7]={192,193,194,195,196,197,198};
byte E10[7]={199,200,201,202,203,204,205};
byte E100[7]={175,176,177,178,179,180,181};
byte E1000[7]={182,183,184,185,186,206,207} ;  
                                                           
void setup()
{
Wire.begin();

// set the initial time here:
// DS3231 seconds, minutes, hours, day, date, month, year
// setDS3231time(00,51,16,5,15,9,16); // SAAT GÜNCELLEME SET AYARI
     pinMode(7,INPUT);
     pinMode(8,INPUT);
  Tlc.init();
}
////////////////////////////////////////////////////////
void readDS3231time(byte *second,byte *minute,byte *hour)
{
Wire.beginTransmission(DS3231_I2C_ADDRESS);
Wire.write(0); // set DS3231 register pointer to 00h
Wire.endTransmission();
Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
// request seven bytes of data from DS3231 starting from register 00h
*second = bcdToDec(Wire.read() & 0x7f);
*minute = bcdToDec(Wire.read());
*hour = bcdToDec(Wire.read() & 0x3f);
}
/////////////////////////////////////////////////
void displayTime()
{
byte second, minute, hour;

readDS3231time(&second, &minute, &hour);

saatGoster(second,minute,hour);
saatGir(second,minute,hour);

}
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void setDS3231time(byte second, byte minute, byte hour)
{

Wire.beginTransmission(DS3231_I2C_ADDRESS);
Wire.write(0); // set next input to start at the seconds register
Wire.write(decToBcd(second)); // set seconds
Wire.write(decToBcd(minute)); // set minutes
Wire.write(decToBcd(hour)); // set hours

Wire.endTransmission();
}
////////////////////////////////////////////////////////
void saatGoster(byte sn,byte dk,byte st){
  st=st%12;
  byte stt=(st*5)+dk/12;
 for(int i=0;i<=sn;i++){
        Tlc.set(saniye[i], 200);
    }
     for(int i=0;i<=dk;i++){
        Tlc.set(dakika[i] , 200);
        
    }
         for(int i=0;i<=stt;i++){
        Tlc.set(saat[i] , 200);
      
    }
      Tlc.update();
  if(sn>58)  { Tlc.clear();}
}

////////////////////////////////////////////////////////////////////////
void saatGir(byte scont,byte minut,byte our){
  byte sny;byte dkk=minut;byte satt=our;
  if(digitalRead(7)==HIGH){
    delay(3000);
    while(digitalRead(7)==HIGH){}
      Tlc.clear();
      Tlc.update();
       sny=0;
      delay(3000);
         while(sny==0){
          if(digitalRead(8)==HIGH){
            dkk++;
            if(dkk>60){dkk=0;}
            saatGoster(sny,dkk,satt);
            while(digitalRead(8)==HIGH){}
            delay(15);
           }
            if(digitalRead(7)==HIGH){sny++;}
            while(digitalRead(7)==HIGH){}
            delay(15);
         }


           while(sny==1){
          if(digitalRead(8)==HIGH){
            satt++;
            if(satt>24){satt=0;}
            saatGoster(sny,dkk,satt);
            while(digitalRead(8)==HIGH){}
            delay(15);
           }
            if(digitalRead(7)==HIGH){sny++;}
            while(digitalRead(7)==HIGH){}
            delay(15);
         }
         
          setDS3231time(sny,dkk,satt);
        if(digitalRead(7)==HIGH){sny++;}
            while(digitalRead(7)==HIGH){}
            delay(15);
    
  }
  
}


void loop()
{
displayTime();
  
    
  }
