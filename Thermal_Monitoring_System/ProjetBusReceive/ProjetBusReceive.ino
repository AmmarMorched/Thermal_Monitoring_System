#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <SD.h>

Servo myServo;
SoftwareSerial mySerial(9, 10);
#define LCD_I2C_ADDRESS 0x27 // I2C address for the LCD
const int chipSelect = 4; // Use pin 4 for chip select

LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, 16, 2);

void setup() {
  myServo.attach(7); // Use pin 4 for servo
  lcd.begin(16, 2);
  lcd.backlight();
  mySerial.begin(9600);
  Serial.begin(9600);

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("Card initialized.");
}
 float temperature;
 
void loop() {
  if (mySerial.available() > 0) {
    String receivedData = mySerial.readStringUntil('\n');
    if (receivedData.startsWith("T=")) {
      receivedData.remove(0, 2); // Remove "T=" from the beginning
       temperature = receivedData.toFloat();

      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");

      // Display temperature on the LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temperature: ");
      lcd.setCursor(0, 1);
      lcd.print(temperature);
      lcd.print(" ");
      lcd.print(char(223));
      lcd.print("C");

      // Log temperature to the SD card
      File dataFile = SD.open("datalog.txt", FILE_WRITE);
      if (dataFile) {
        dataFile.print("Temperature: ");
        dataFile.print(temperature);
        dataFile.println(" °C");
        dataFile.close();
        Serial.println("Temperature logged to file.");
      } else {
        Serial.println("Error opening or writing to datalog.txt");
      }
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(receivedData);
      lcd.setCursor(0, 1);
      lcd.print(temperature);
      funServo1();
      delay(1000);
      funServo2();
    }
  }
}

void funServo2() {
  // Move the servo to the 180-degree position
  myServo.write(180);
  myServo.write(90);
  myServo.write(0);
  delay(1000);  // Wait for 1 second
}

void funServo1() {
  // Move the servo to the 0-degree position
  myServo.write(0);
  myServo.write(90);
  myServo.write(180);
  delay(1000);  // Wait for 1 second
}
