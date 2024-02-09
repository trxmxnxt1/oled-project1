#include <SPI.h> // เรียกใช้ library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFi.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1); // ขนาดของหน้าจอ
//Adafruit_SH1106 oled(21,22); //21=SDA ,22=SCK

char ssid[] = "thiramanat_2.4G";
char pass[] = "newin11111";

#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     7
#define UTC_OFFSET_DST 0

#define buzzer 5 // Buzzer

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, UTC_OFFSET);

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    oled.setCursor(0, 1);
    oled.println("Connection Err");
    return;
  }

  oled.setCursor(8, 0);
  oled.println(&timeinfo, "%H:%M:%S");

  oled.setCursor(0, 1);
  oled.println(&timeinfo, "%d/%m/%Y   %Z");
}

void oledCustomMessage(const char* message) {
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println(message);
  oled.display();
}

void setup() {
  Serial.begin(115200);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // เรียกใช้บอร์ด
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.print("Connecting to ");
  oled.setCursor(0, 1);
  oled.print("WiFi ");

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.print("Online");
  oled.setCursor(0, 1);
  oled.println("Updating time...");

  configTime(UTC_OFFSET * 3600, UTC_OFFSET_DST, NTP_SERVER);
}


void loop() {
  printLocalTime();
  delay(1000);

  // Example: oled a custom message after 10 seconds
  if (millis() > 10000) {
    oledCustomMessage("Hello, OLED!");
  }
}
