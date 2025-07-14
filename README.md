# 🌿 Smart Room Environment Control System Based on IoT

This project implements a smart system to monitor and control the room environment using an IoT-based approach. The system utilizes the **ESP8266 NodeMCU** microcontroller combined with a **DHT22 sensor** to measure temperature and humidity in real-time. Based on the measured temperature, the system automatically adjusts:

- **AC Lamp Brightness** using a dimmer module
- **Relay Outputs** to control additional devices

All data and device status are visualized and controlled via the **Blynk IoT application**, enabling remote monitoring from anywhere.

---

## 🔧 Features

- Real-time temperature and humidity monitoring
- Automatic lamp dimming based on temperature thresholds
- Dual relay control for fan, cooler, or other appliances
- Integration with Blynk IoT for cloud monitoring and control
- Serial Monitor output for local debugging

---

## ⚙️ How It Works

- If **temperature < 30°C**:
  - Lamp is set to **100% brightness**
  - Relays are **OFF**
- If **30°C ≤ temperature < 33°C**:
  - Lamp is set to **50% brightness**
  - Relays are **OFF**
- If **temperature ≥ 33°C**:
  - Lamp is **OFF**
  - Relays are **ON** (e.g., to trigger ventilation or alarms)

---

## 📡 Technologies Used

- **ESP8266 NodeMCU** for WiFi and control logic
- **DHT22** sensor for temperature and humidity readings
- **RBDdimmer** library to control lamp brightness
- **Blynk** platform for cloud dashboard and virtual pins

---

## 📲 Mobile Dashboard (Blynk)

| Virtual Pin | Description             |
|-------------|-------------------------|
| V0          | Temperature (°C)        |
| V1          | Humidity (%)            |
| V2          | Lamp Brightness (%)     |
| V3          | Relay 1 Status          |
| V4          | Relay 2 Status          |

---

## ⚙️ Wiring Diagram

| Component       | NodeMCU Pin | Notes                         |
|------------------|--------------|-------------------------------|
| DHT22 (Data)     | D4 (GPIO2)   | With 10k pull-up resistor     |
| Dimmer Output    | D6 (GPIO12)  | Connect to dimmer control pin |
| Zero Cross Input | D5 (GPIO14)  | Required for RBDdimmer        |
| Relay 1 Signal   | D1 (GPIO5)   | Connect to IN1 of relay       |
| Relay 2 Signal   | D2 (GPIO4)   | Connect to IN2 of relay       |

> ⚠️ Ensure proper isolation and safety when working with AC dimmer circuits and relays.

---

## 🧰 Hardware Requirements

- 1x **NodeMCU ESP8266**
- 1x **DHT22 sensor**
- 1x **AC Dimmer module** (compatible with RBDdimmer library)
- 2x **Relay modules**
- Jumper wires, breadboard, or PCB
- Optional: External 5V power supply (for relays)
- Stable **WiFi connection**
- **Smartphone with Blynk IoT App** installed

---

## ⬆️ Upload Instructions

1. Open the Arduino IDE
2. Install the following libraries:
   - `Blynk`
   - `ESP8266WiFi`
   - `DHT sensor library`
   - `RBDdimmer`
3. Connect your NodeMCU to the PC via USB
4. Copy and paste the code into Arduino IDE
5. Enter your **WiFi SSID**, **Password**, and **Blynk Auth Token**
6. Select board: `NodeMCU 1.0 (ESP-12E Module)`
7. Upload the code
8. Open Serial Monitor at `9600 baud` to verify sensor readings
9. Open Blynk app and add widgets for:
   - V0 (Gauge – Temperature)
   - V1 (Gauge – Humidity)
   - V2 (Display or Slider – Lamp Power)
   - V3 & V4 (LED or Button – Relay status)

---

