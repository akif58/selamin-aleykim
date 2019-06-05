#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
return( (val/10 * 16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
return( (val/16 * 10) + (val%16) );
}
///////////////////////////////////////////////////////7
void setup()
{
Wire.begin();
Serial.begin(9600);
// set the initial time here:
// DS3231 seconds, minutes, hours, day, date, month, year
// setDS3231time(00,51,16,5,15,9,16); // SAAT GÜNCELLEME SET AYARI
}
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
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

readDS3231time(&second, &minute, &hour);

Serial.print(second, DEC);
Serial.print(" ");
Serial.print(dayOfMonth, DEC);
Serial.print("/");
Serial.print(month, DEC);
Serial.print("/");
Serial.print(year, DEC);
Serial.print(" Day of week: ");

}
void loop()
{
displayTime(); // display the real-time clock data on the Serial Monitor,

}
