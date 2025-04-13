cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Set the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin();
  lcd.begin(16, 2);
  lcd.backlight();
  dht.begin();
  
  Serial.begin(9600);
  delay(1000); 
  Serial.println("DHT and LCD Ready!");
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor error");

    Serial.println("Failed to read from DHT sensor!");
    
    delay(2000);
    return;
  }

  // Print to LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print((char)223); // Degree symbol °
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.print("%");

  // Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C\tHumidity: ");
  Serial.print(hum);
  Serial.println(" %");

  delay(2000);
}
