#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char *WIFI_SSID = "OnePlus";
const char *WIFI_PWD = "password11";
const char* webAppUrl = "https://script.google.com/macros/s/AKfycbxaim8rdorakuwsdA_ViLaX6qRDYDgDoRlC9U1IA7GPMTAfBirCxEvFPNiotDWkKIyS/exec";

WiFiClient wifiClient;
Adafruit_MPU6050 mpu;

void ConnectToWiFi() {
  Serial.print("Connecting to WiFi ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PWD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nConnected to ");
  Serial.println(WIFI_SSID);
}

void SetupMpu6050() {
  if (!mpu.begin(0x69)) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
  }
}

// Send data to Google Sheets
void setup() {
  Serial.begin(115200);
  Serial.println("Setup begin");

  ConnectToWiFi();
  SetupMpu6050();

  Serial.println("Setup end");
}

void loop() {
  static uint64_t last_time = 0;
  uint64_t now = millis();
float xv,yv,zv;
  if (now - last_time > 5000) {  // Every 5 seconds
    // Get new sensor events with the readings.
    sensors_event_t a, g, mpu_temp;
    mpu.getEvent(&a, &g, &mpu_temp);

    // Print acceleration values
    Serial.print("Acceleration X: ");
    Serial.print(a.acceleration.x);
    Serial.print(", Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(", Z: ");
    Serial.print(a.acceleration.z);
    xv = float(a.acceleration.x);
    yv = float(a.acceleration.y);
    zv = float(a.acceleration.z);
    // Send data to the web server
    sendDataToScript(xv, yv, zv);

    last_time = now;
  }

  delay(5000);  // Delay for 5 seconds
}

void sendDataToScript(float x_axis, float y_axis, float z_axis) {
  HTTPClient http;

  // Construct the server path
  String serverPath = String(webAppUrl) + "?x_axis=" + String(x_axis) + "&y_axis=" + String(y_axis) + "&z_axis=" + String(z_axis);

  Serial.print("Connecting to server: ");
  Serial.println(serverPath);

  // Send HTTP GET request
  if (http.begin(serverPath)) {
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.print("Server response code: ");
      Serial.println(httpCode);
    } else {
      Serial.print("HTTP GET request failed with error code: ");
      Serial.println(httpCode);
    }
    http.end();
  } 
  else {
    Serial.println("Unable to connect to the server");
  }
}
