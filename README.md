## Vibration Fault Detection Using ESP32 & MPU6050
This project involves real-time vibration data collection, fault detection, and dashboard monitoring using an ESP32 microcontroller and MPU6050 sensor. It aims to enable predictive maintenance for machinery by classifying vibration patterns into normal or faulty states using machine learning.
---

## Hardware Requirements
- **ESP32** Microcontroller  
- **MPU6050** Accelerometer and Gyroscope Sensor  
- Jumper Wires, USB Cable  
- Power Supply (if not using USB)
---

## Software Requirements
- **Arduino IDE** (for programming ESP32)
- **Google Sheets** (to log real-time data)
- **Google Apps Script** (for Web App endpoint)  
- **Google Colab** ( for trainingMachine Learing model)
- **Python** (for data preprocessing and ML model)  
---

## Installation and Setup

### Connect MPU6050 to ESP32
| MPU6050 Pin | ESP32 Pin |
|-------------|-----------|
| VCC         | 3.3V      |
| GND         | GND       |
| SDA         | GPIO21    |
| SCL         | GPIO22    |
| AD0         | 3.3V      |

![image](https://github.com/user-attachments/assets/94245c54-dafd-4e2c-9fb2-6dd8d36cf1d0)


### Arduino IDE Setup
- Install **ESP32 Board Support**  
- Board: ESP32 Dev Module
- Install Libraries:
  - Adafruit_MPU6050.h
  - Adafruit_Sensor.h
  - WiFi.h
  - HTTPClient.h
- Write the sketch with the Google Apps Script Web App URL in it.

### Google Sheets Setup
- Create a Google Sheet with appropriate columns (e.g. Date, Time, X_axis, Y_axis, Z_axis)
- Go to **Extensions > Apps Script**, and write the script to publish as a Web App.

### Machine Learning Initialization
- Install all the required Python Libraries.
- Export your Google Sheets data as raw_data.csv
- Train & test the ML model.
- Save the model.
- From Google cloud console generate a .json source file for the code to access the updating google sheet.
- Deploy the model.
