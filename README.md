# AutoLightIQ 
> An intelligent, IoT-driven streetlight management system for urban energy efficiency.

[![Platform](https://img.shields.io/badge/Platform-NodeMCU%20V3-blue)](https://www.nodemcu.com/)
[![Language](https://img.shields.io/badge/Language-C++%20(Arduino)-orange)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

---

## Overview 📖
**AutoLightIQ** automates urban illumination using the **ESP8266** microcontroller. Traditional streetlights waste energy by staying on all night; this system uses a "light-on-demand" approach.

![Project Hero Image](https://github.com/user-attachments/assets/88c96761-bb7c-4b40-ad34-0cefb9ff7fb4)

### The Problem 📉
Static timers for streetlights lead to significant energy waste during inactivity and daylight.

### Our Solution 🚀
A tiered decision-making framework:
1. **LDR Sensor:** Detects if it is night or day. If bright, system stays dormant.
2. **IR Sensor Array:** Once dark, the system waits for motion.
3. **LED Bank:** Triggers 4 LEDs only when movement is detected.
4. **OTA Management:** WiFi integration allows for remote firmware updates.

---

### 🏆 Exhibition & Recognition
I had the honor of showcasing **AutoLightIQ** at the **PNT Labs Expo 2025**, hosted at my college. The project demonstrated real-time energy savings through automated sensor logic.

![PNT Labs Expo 2025](https://github.com/user-attachments/assets/81a12f4f-82bd-467d-946c-76bc0a884f49)


## 🛠️ Hardware Components

| Component | Quantity | Purpose |
| :--- | :---: | :--- |
| **NodeMCU V3 (ESP8266)** | 1 | Main Controller & WiFi Hub |
| **IR Proximity Modules** | 2 | Motion detection |
| **LDR Module** | 1 | Ambient light sensing |
| **LED Bulbs** | 4 | Streetlight simulation |
| **Breadboard/Jumper Wires** | ~ 35-40 | Physical connections |

### Component Gallery
<table>
  <tr>
    <td align="center"><img src="https://github.com/user-attachments/assets/7195f98c-f6e8-4925-abd0-fe525d3137e9" width="300px"/><br/><sub><b>NodeMCU ESP8266 V3</b></sub></td>
    <td align="center"><img src="https://github.com/user-attachments/assets/2f1a10e5-f4f9-4a9b-b690-77d2727140fa" width="200px"/><br/><sub><b>Start Infrared (IR) Sensor</b></sub></td>
    <td align="center"><img src="https://github.com/user-attachments/assets/98a80650-e514-4977-8740-752333a51fa7" width="200px"/><br/><sub><b>End Infrared (IR) Sensor</b></sub></td>
    <td align="center"><img src="https://github.com/user-attachments/assets/5a458e96-b24d-497c-820f-12be8eaa5a6b" width="300x"/><br/><sub><b>Light Dependent Resistor (LDR) Module</b></sub></td>
  </tr>
</table>

---
## 🛡️ Disclaimer

I personally executed the complete physical assembly and wiring of this project. Being **my first experience** with the NodeMCU and ArduinoIDE platform, I fully admit to using **AI** tools to help bridge the gap in my technical knowledge, that is to generate the majority of the code. However, every connection and line of code was reviewed by me, as the code is in **C++**, which is very similar to **C** that I am familiar with.

## ⚙️ How it Works (Logic Flow)
```mermaid
graph TD
    A[Start] --> B{Is it Dark? - LDR}
    B -- No --> C[LEDs OFF / Sleep]
    B -- Yes --> D{Motion Detected? - IR}
    D -- No --> E[LEDs OFF / Standby]
    D -- Yes --> F[Trigger LEDs]
    F --> G[Wait for Clear]
    G --> B
