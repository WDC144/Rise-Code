#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Wire.h>
#include <Adafruit_ADXL343.h>
#include <SD.h>


const int chipSelect = 10;

#define BMP388_I2C_ADDR 0x77
#define ADXL343_I2C_ADDR 0x53


Adafruit_BMP3XX bmp;
Adafruit_ADXL343 accel = Adafruit_ADXL343(12345) ;
File = SD.open("dataFile0.txt",FILE_WRITE);
if(dataFile0.read()==NULL){
  dataFile0.print(0);
}
int doc = (dataFile0.read());
dataFile0.print(doc+1);
dataFile0.close();
File dataFile;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  if (!bmp.begin_I2C(BMP388_I2C_ADDR)) {
    Serial.println("Could not find a valid BMP388 sensor, check wiring!");
    while (1);
  }

  if (!accel.begin(ADXL343_I2C_ADDR)) {
    Serial.println("Could not find a valid ADXL343 sensor, check wiring!");
    while (1);
  }
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  dataFile = SD.open("data.txt", FILE_WRITE);

  if (!dataFile) {
    Serial.println("Error opening data file");
    while (1);
  }

  dataFile.println("Temperature, Pressure, X, Y, Z");
  dataFile.close();
  // delay(60000);
}

void loop() {
  float st = millis();
  sensors_event_t event;
  float T1 = bmp.readTemperature();
  float P1 = bmp.readPressure() / 100.0;

  sensors_event_t accel_event;
  accel.getEvent(&accel_event);
  float x = accel_event.acceleration.x;
  float y = accel_event.acceleration.y;
  float z = accel_event.acceleration.z;

 File dataFile = SD.open("data.txt", FILE_WRITE);
if (dataFile) {
  dataFile.print(String(T1));
  dataFile.print(",");
  dataFile.print(String(P1));
  dataFile.print(",");
  dataFile.print(String(x));
  dataFile.print(",");
  dataFile.print(String(y));
  dataFile.print(",");
  dataFile.println(String(z));

dataFile.close();

  Serial.print(String(T1));
  Serial.print(",");
  Serial.print(String(P1));
  Serial.print(",");
  Serial.print(String(x));
  Serial.print(",");
  Serial.print(String(y));
  Serial.print(",");
  Serial.println(String(z));

}

  else {
    Serial.println("error opening data.txt");
  }

  delay(1000);
  
  // while(st = 6000){
  // exit(0);
  // }
}
