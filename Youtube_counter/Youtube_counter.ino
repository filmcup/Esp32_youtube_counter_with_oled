// Powered By Arduino classroom Youtube Channel

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <YoutubeApi.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);


const char ssid[] = "Your WIFI Router SSID";
const char password[] = "Your WIFI Router Password";

#define API_KEY "Enter Your API key"
#define CHANNEL_ID "Enter Your Channel ID"

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long timeBetweenRequests = 60 * 1000;  // 60 seconds, in milliseconds

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
  display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
  display.setTextSize(1); // กำหนดขนาดตัวอักษร
  display.setTextColor(WHITE);
  display.setCursor(0,0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
  display.println(" OLED 0.96 TESTER ");
  display.setCursor(0,10);
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE); //กำหนดข้อความสีขาว ฉากหลังสีดำ
  display.println(" Myarduino");
  display.setCursor(0,32);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("128 x 64 Pixels 0.96");
  display.setCursor(0,48);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" www.myarduino.net "); // แสดงผลข้อความ www.Myarduino.net
  display.display();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("\nConnecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  client.setInsecure();
}

void loop() {
  if (api.getChannelStatistics(CHANNEL_ID)) {
    Serial.println("\n---------Stats---------");

    Serial.print("Subscriber Count: ");
    Serial.println(api.channelStats.subscriberCount);

    Serial.print("View Count: ");
    Serial.println(api.channelStats.viewCount);

    Serial.print("Video Count: ");
    Serial.println(api.channelStats.videoCount);

    Serial.println("------------------------");

    display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
    display.setTextSize(1); // กำหนดขนาดตัวอักษร
    display.setTextColor(WHITE);
    display.setCursor(0,0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
    
    display.println("\n---------Stats---------");

    display.print("Subscriber Count: ");
    display.println(api.channelStats.subscriberCount);

    display.print("View Count: ");
    display.println(api.channelStats.viewCount);

    display.print("Video Count: ");
    display.println(api.channelStats.videoCount);

    display.println("------------------------");

    display.display();
  }
  delay(timeBetweenRequests);
}
