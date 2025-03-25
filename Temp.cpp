#include <DHT.h>
#include <LiquidCrystal.h>

// Define pin connections
#define DHT_PIN 7   // Digital pin for DHT11 sensor
#define DHT_TYPE DHT11
#define LED_PIN 10
#define BUZZER_PIN 9

// Initialize DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Set up LCD connections
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define thresholds
int tempThreshold = 25;     
int humidityThreshold = 60;  

void setup() {
  lcd.begin(16, 2);
  lcd.print("Env Monitor");

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if sensor data is valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT sensor error!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error! ");
    return;
  }

  // Debug output
  Serial.print("Temp: "); Serial.print(temperature);
  Serial.print(" | Humidity: "); Serial.println(humidity);

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Humidity: "); lcd.print(humidity); lcd.print("%   ");

  lcd.setCursor(0, 1);
  lcd.print("Temp: "); lcd.print(temperature); lcd.print("C   ");

  // Check thresholds
  if (temperature > tempThreshold || humidity > humidityThreshold) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.setCursor(12, 1);
    lcd.print("ALERT!");
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    lcd.setCursor(12, 1);
    lcd.print("       ");
  }

  delay(2000);
}
