#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// 1. اسم شبكة الواي فاي اللي الـ ESP32 هيعملها والباسورد
const char* ssid = "ESP32_Cat_Network";
const char* password = "password123"; // لازم يكون 8 أرقام/حروف أو أكتر

// إنشاء سيرفر على المنفذ 80
WebServer server(80);

// الدالة المسئولة عن عرض الصفحة
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta charset='UTF-8'><title>ESP32 Cat AP</title></head>";
  html += "<body style='text-align: center; font-family: Arial; background-color: #222; color: white; margin-top: 50px;'>";
  html += "<h1>Meow from ESP32 Hotspot! 🐾</h1>";
  
  // محاولة عرض صورة من النت (هتظهر لو فاتح داتا الموبايل)
  html += "<p style='color: #aaa;'>Real photo (Needs Data):</p>";
  html += "<img src='https://cataas.com/cat' width='300' style='border-radius: 15px;' alt='No Internet for real photo'>";
  
  // رسمة قطة مدمجة في الكود هتظهر دايماً بدون نت
  html += "<p style='color: #aaa; margin-top: 30px;'>Offline Code Cat:</p>";
  html += "<svg width='150' height='150' viewBox='0 0 100 100'>";
  html += "<circle cx='50' cy='50' r='40' fill='#555' />"; // الوجه
  html += "<polygon points='15,20 30,50 10,50' fill='#555' />"; // ودن يمين
  html += "<polygon points='85,20 70,50 90,50' fill='#555' />"; // ودن شمال
  html += "<circle cx='35' cy='45' r='6' fill='white' /><circle cx='35' cy='45' r='2' fill='black' />"; // عين يمين
  html += "<circle cx='65' cy='45' r='6' fill='white' /><circle cx='65' cy='45' r='2' fill='black' />"; // عين شمال
  html += "<ellipse cx='50' cy='60' rx='8' ry='5' fill='pink' />"; // الأنف
  html += "</svg>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  // تشغيل الـ ESP32 كـ Access Point (هوت سبوت)
  Serial.println("\nStarting Access Point...");
  WiFi.softAP(ssid, password);

  // طباعة عنوان الـ IP (الافتراضي في الغالب بيكون 192.168.4.1)
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Hotspot Started! IP address: ");
  Serial.println(IP);

  // ربط الرابط الرئيسي بالدالة
  server.on("/", handleRoot);
  
  // تشغيل السيرفر
  server.begin();
}

void loop() {
  server.handleClient();
}