# Arduino-based-Smart-Plant-Watering-System-Self-Learning-with-Led-Indication

An **Arduino-based automatic plant watering system** that monitors soil moisture and intelligently controls a water pump.
This system includes a **self-learning mechanism** that dynamically adjusts watering thresholds based on real soil conditions, making it more adaptive than traditional fixed-threshold systems.
---

## Features

  **Soil Moisture Monitoring**

  * Reads real-time moisture levels using an analog soil sensor
  * Displays moisture levels via Serial Monitor

  **Visual Moisture Indicator (LED Bar)**

  * 5 LEDs represent soil condition:

    * Very Wet → Very Dry
  * Quick visual feedback without needing a screen

  **Automatic Water Pump Control**

  * Turns pump ON when soil is too dry
  * Turns pump OFF when soil is sufficiently wet

  **Self-Learning Threshold System**

  * Continuously analyzes soil moisture readings
  * Automatically adjusts:

    * Dry threshold
    * Wet threshold
  * Adapts to different soil types and environments

  **Sensor Protection**

  * Powers soil sensor only during readings
  * Reduces corrosion and increases sensor lifespan

---

## Hardware Components

* Arduino (Uno / Nano / compatible)
* Soil moisture sensor (analog)
* Water pump (with relay or transistor driver)
* 5 LEDs
* Resistors (for LEDs)
* Jumper wires
* External power supply (recommended for pump)

---

## Pin Configuration

| Component          | Arduino Pin |
| ------------------ | ----------- |
| Soil Sensor VCC    | A0          |
| Soil Sensor Signal | A1          |
| Pump Control       | 7           |
| LED 1 (Dry)        | 8           |
| LED 2              | 9           |
| LED 3              | 10          |
| LED 4              | 11          |
| LED 5 (Wet)        | 12          |

---

## How It Works

1. **Moisture Reading**

   * The sensor is powered ON briefly to take a reading.
   * After reading, it is turned OFF to prevent corrosion.

2. **LED Indication**

   * Moisture values are mapped to 5 levels:

     * 0–200 → Very Wet
     * 200–400 → Wet
     * 400–600 → Normal
     * 600–800 → Dry
     * 800+ → Very Dry

3. **Self-Learning Algorithm**

   * The system collects 100 samples (~10 seconds).
   * Calculates the average moisture.
   * Adjusts:

     * `wetThreshold` if soil is wetter than expected
     * `dryThreshold` if soil is drier than expected

4. **Pump Control Logic**

   * If moisture > dryThreshold → Pump ON (soil is dry)
   * If moisture < wetThreshold → Pump OFF (soil is wet)

---

## Serial Output

The system prints:

* Current moisture value
* Updated thresholds (after learning cycle)
* Pump status (ON / OFF)

---

## Advantages

* No manual calibration required
* Adapts to different soil types automatically
* Extends sensor lifespan
* Simple and low-cost implementation

---

## Possible Improvements

* Add LCD/OLED display for real-time data
* Integrate WiFi for remote monitoring (IoT)
* Add water level sensor for tank safety
* Use capacitive moisture sensor for better durability
* Implement scheduling (watering at specific times)

---

## License

Open-source project – free to use, modify, and improve.
