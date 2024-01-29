Project Description:
This project is an Arduino-powered parking management system designed to monitor parking slots using four infrared (IR) sensors and manage entry and exit states with two additional sensors. It features a servo motor that acts as a parking gate, which raises and lowers to allow vehicles to enter or exit. The system status, including available parking slots and gate state, is displayed on an I2C LCD.

Features:

  Real-time monitoring of parking slots using IR sensors.
    Entry and exit gate control with a servo motor.
    Status display on a 16x2 I2C LCD.
    Simple simulation of a parking gate system for educational purposes.

Hardware Components:

   1. 1 x Arduino Uno
   2. 4 x IR sensors for slot detection
   3. 2 x IR s  ensors for entry/exit detection
   4. 1 x Servo Motor (Tower Pro SG90) for gate operation
   5. 1 x I2C LCD display (16x2 characters)
   6. Jumper wires and breadboard for connections

Software and Libraries:

  1. Arduino IDE for code upload.
  2. Wire.h for I2C communication with the LCD.
  3. LiquidCrystal_I2C.h for interfacing with the LCD.
  4. Servo.h for controlling the servo motor.
  5. Custom .ino Arduino sketch (source code provided).

How It Works:
The system uses IR sensors to detect the presence of vehicles in parking slots and at the entry/exit points. When a vehicle approaches the entry point, the servo motor gate is activated to open, allowing the vehicle to park. If a slot is available, the LCD displays the number of open slots; if not, it indicates that the parking is full. The exit sensor works similarly to allow vehicles to leave.

Setup Instructions:

  1. Assemble the hardware components according to the provided circuit diagram.
  2. Connect the Arduino to your computer via USB.
  3. Open the .ino file with the Arduino IDE.
  4. Install the required libraries through the Library Manager in the Arduino IDE.
  5. Upload the sketch to the Arduino Uno.
  6. The system will start monitoring the parking slots and gate entry/exit.

Limitations:

  1. The gate operation is based on a delay function which may not be ideal for real-time response requirements.
  2. The current system does not handle the scenario of two vehicles entering or exiting simultaneously, which could lead to incorrect slot monitoring or gate operation.

Potential Solutions:

  3. To address the delay issue, an interrupt-based system could be implemented to handle gate operation more efficiently.
  4. Implementing additional sensors and logic could resolve the multi-vehicle entry/exit problem, ensuring accurate slot counts and gate management.

Code Structure:
The source code is organized into functions for initializing the hardware, monitoring parking slots, controlling the gate, and updating the LCD. The logic can be customized to accommodate different parking lot sizes or additional features.

This system serves as a prototype to demonstrate the capabilities of Arduino in managing a parking system and provides a platform for students to explore sensor integration, real-time monitoring, and automated control systems.
