#include <Wire.h>
#include <SoftwareSerial.h>

#include <Adafruit_TCS34725.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);// inicialisation de capteur RGB

int redPin = 7;  // Connect the LED to digital pin 9
int yellowPin=6;
int buttonPin = 5;
SoftwareSerial mySerial(9, 10);
#define DS1621_I2C_ADDRESS 0x48 // DS1621 I2C address

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  Wire.begin();
    if (!tcs.begin()) {
    Serial.println("Could not find a valid TCS34725 sensor, check wiring!");
    while (1);
  }
  Serial.println("Color Sensor TCS34725 found!");

}

void loop() {

   
  uint16_t c = tcs.read16(TCS34725_CDATAL) + tcs.read16(TCS34725_CDATAH); // valider les couleur du capteur

  Serial.print("Clear: ");
  Serial.print(c); 
  Serial.print(" ");
  Serial.println();

  // Adjust the LED based on the intensity of the detected color
  analogWrite(redPin,  map(c, 0, 65535, 0, 255));

  
  float temperature = readTemperature();
  
  

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  if ( digitalRead(buttonPin) == HIGH ){
  analogWrite(yellowPin,LOW);
  // Send temperature through UART
  mySerial.print("T=");
  mySerial.print(temperature);
  mySerial.println("C");
  
  delay(1000); // Delay for 1 second
  
  }
  else if ( digitalRead(buttonPin) == LOW ) {
    analogWrite(yellowPin,LOW);
    // Send temperature through UART
    if ( temperature > 20.00 ) {
      mySerial.print("Valeur > Seuil   ");
      analogWrite(yellowPin,HIGH);
    }
    else if ( temperature <= 20.00 ){
      analogWrite(yellowPin,LOW);
      mySerial.print("Valeur < Seuil   ");
      }
      delay(1000); // Delay for 1 second
    }
}
/////
float readTemperature() {
  Wire.beginTransmission(DS1621_I2C_ADDRESS);
  Wire.write(0xEE); // Start temperature conversion
  Wire.endTransmission();
  delay(750);

  // Read temperature
  Wire.beginTransmission(DS1621_I2C_ADDRESS);
  Wire.write(0xAA); // Read temperature command
  Wire.endTransmission();

  Wire.requestFrom(DS1621_I2C_ADDRESS, 2);

  byte highByte = Wire.read();
  byte lowByte = Wire.read();
  int rawTemperature = (highByte << 8) | lowByte;
  float temperature = rawTemperature / 256.0;

  return temperature;
}
