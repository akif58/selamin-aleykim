#include "Wire.h" 
#define DS3231_I2C_ADDRESS 0x68

// Normal ondalık sayıları ikili kodlanmış ondalık 
baytlara dönüştürün decToBcd (byte val) 
{ 
return ((val / 10 * 16) + (val% 10)); 
} 
// İkilik kodlu ondalık sayıyı normal ondalık sayılara dönüştürün 
byte bcdToDec (byte val) 
{ 
return ((val / 16 * 10) + (val% 16)); 
} 
void setup () 
{ 
Wire.begin (); 
Serial.begin (9600); 
// başlangıç ​​saatini buraya ayarlayın: 
// DS3231 saniye, dakika, saat, gün, tarih, ay, yıl 
// setDS3231time (00,51,16,5,15,9,16); // SAAT GÜNCELLEME SET AYARI 
}

boşluk setDS3231time (bayt saniye, bayt dakika, bayt saat, bayt 
günOfWeek, bayt günOfMonth, bayt ay, bayt yıl) 
{ 
// saat ve tarih verisini DS3231 olarak ayarlar 
Wire.beginTransmission (DS3231_I2C_ADDRESS); 
Wire.write (0); // saniye cinsinden başlayacak bir sonraki girişi ayarlayın 
Wire.write (decToBcd (second)); // saniye 
ayarla Wire.write (decToBcd (dakika)); // dakika ayarlamak 
Wire.write (decToBcd (hour)); // saat ayarlandı 
Wire.write (decToBcd (dayOfWeek)); // haftanın gününü ayarla (1 = Pazar, 7 = Cumartesi) 
Wire.write (decToBcd (dayOfMonth)); // tarihi ayarla (1 - 31) 
Wire.write (decToBcd (month)); // ayı 
ayarla Wire.write (decToBcd (year)); // set yılı (0 - 99) 
Wire.endTransmission (); 
}
geçersiz okuma DS3231time (bayt * saniye, 
bayt * dakika, 
bayt * saat 
, 
bayt * günOfWeek; 
bayt * dayOfMonth, bayt * ay, 
bayt * yıl) 
{ 
Wire.beginTransmission (DS3231_I2C_ADDRESS); 
Wire.write (0); // DS3231 kayıt göstergesini 00h olarak 
ayarlayın Wire.endTransmission (); 
Wire.requestFrom'dan (DS3231_I2C_ADDRESS, 7); 
// 0032 
* register'ından başlayarak DS3231'den yedi bayt veri isteyin, 00h * second = bcdToDec (Wire.read () & 0x7f); 
* minute = bcdToDec (Wire.read ()); 
* hour = bcdToDec (Wire.read () & 0x3f); 
* dayOfWeek = bcdToDec (Wire.read ()); 
* dayOfMonth = bcdToDec (Wire.read ()); 
* month = bcdToDec (Wire.read ());
* yıl = bcdToDec (Wire.read ()); 
}

void displayTime () 
{ 
bayt saniye, dakika, saat, dayOfWeek, dayOfMonth, ay, yıl; 
// DS3231 
okumaDS3231time'dan (& saniye, & dakika, & saat, & dayOfWeek, & dayOfMonth, & month, 
& year) verileri al 
// seri monitöre gönder 
Serial.print (hour, DEC); 
// görüntülendiğinde bayt değişkenini ondalık sayıya dönüştürün 
Serial.print (":"); 
eğer (dakika <10) 
{ 
Seri.print ("0"); 
} 
Seri.print (dakika, DEC); 
Serial.print ( ":"); 
if (second <10) 
{ 
Seri.print ("0"); 
} 
Seri.print (ikinci, DEC); 
Seri baskı (""); 
Seri.
Serial.print ( "/"); 
Seri baskısı (ay, Aralık); 
Serial.print ( "/"); 
Seri baskısı (yıl, Aralık); 
Serial.print ("Haftanın günü:"); 
anahtar ( dayOfWeek ) { 
vaka 1: 
Seri.println ("Pazar"); 
break; 
durum 2: 
Seri.println ("Pazartesi"); 
break; 
durum 3: 
Seri.println ("Salı"); 
break; 
durum 4: 
Seri.println ("Çarşamba"); 
break; 
vaka 5: 
Seri.println ("Perşembe"); 
break; 
durum 6: 
Seri.println ("Cuma"); 
break; 
durum 7: 
Seri.println ("Cumartesi"); 
break;




displaytime (); // Seri Monitörde gerçek zamanlı saat verilerini gösterir, 
gecikme (1000); // her saniye 
}
