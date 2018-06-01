#include <DHT12.h>
#include <Wire.h>          // DHT12 uses I2C (GPIO4=SDA, GPIO5=SCL)
DHT12 dht12;               // Default Unit = CELSIUS, ID = 0x5c
 
const int pinLED = 2;      // On-board LED of ESP-12
const unsigned long sleepTime = 3000000;
 
void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("***** DHT12 Test *****");
  


}
 
void loop() {
  
  
  Serial.print("* Temperature (℃) = ");
  Serial.println(dht12.readTemperature(), 1);
 
  Serial.print("* Relative Humidity (%) = ");
  Serial.println(dht12.readHumidity(), 1);
 
  Serial.println("-------------------------------");

  delay(1000);             // Do not use delayMicrosenconds() (--> Soft WDT Error)
}
 

