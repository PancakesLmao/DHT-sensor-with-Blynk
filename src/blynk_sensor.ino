// SETUP BLYNK
#define BLYNK_TEMPLATE_ID "BLYNK_ID"
#define BLYNK_TEMPLATE_NAME "BLYNK_NAME"
#define BLYNK_AUTH_TOKEN "BLYNK_TOKEN"

#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27, 20, 4);
// SETUP DHT22
#define DHTPIN 2 // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// #define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
// #define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
// define pin data

// //HTTP ESP32 SETUP
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// Defining the WiFi channel speeds up the connection:
#define WIFI_CHANNEL 6

int alert = 0;

void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("DHT22 test!"));

  dht.begin();

  // LED SETUP
  pinMode(18, OUTPUT);

  // DHT22 SETUP
  Serial.begin(115200); // 1bit=10µs

  // LCD SETUP
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Connecting to ");
  LCD.setCursor(0, 1);
  LCD.print("WiFi ");

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.println("Online");
  LCD.setCursor(0, 1);
  LCD.println("Updating time...");

  // BLYNK SETUP
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop(void)
{
  // run blynk
  Blynk.run();

  // LED BLINK
  digitalWrite(18, HIGH); // turn the LED on
  delay(1000);            // wait for 500 milliseconds
  digitalWrite(18, LOW);  // turn the LED off
  delay(1000);            // wait for 500 milliseconds
  //
  delay(5000); // 5s between each reading
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  if (h > 60 || t > 40)
  {                        // Check if humidity > than 55% or temp > 40
    digitalWrite(8, HIGH); // Turn on the LED
    alert = 1;
  }
  else
  {
    digitalWrite(8, LOW); // Turn off the LED
    alert = 0;
  }
  if (t > 40)
  {                        // Check if temp is higher than 40
    digitalWrite(8, HIGH); // Turn on the LED
  }
  else
  {
    digitalWrite(8, LOW); // Turn off the LED
  }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, alert);

  // LCD DISPLAY
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Temp: ");
  LCD.print(t);
  LCD.print("'C");
  LCD.setCursor(0, 1);
  LCD.print("Humidity:");
  LCD.print(h);
  LCD.print("%");
  LCD.display();

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F "));
  Serial.println(F(""));
}
