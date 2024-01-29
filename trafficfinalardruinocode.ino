/*
By:- Unmesh Subedi
github:- https://github.com/Celestial071
*/


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD and IR sensor pins
const int en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
LiquidCrystal_I2C lcd(0x27, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
Servo mymotor;
Servo mymotor1;

// IR sensor pins for entry/exit and parking slots
int IR1_Pin = 2;
int IR2_Pin = 3;
int slot1_Pin = 4;
int slot2_Pin = 5;
int slot3_Pin = 6;
int slot4_Pin = 7;

// Define states for the state machine
enum State {
    IDLE,
    CAR_ENTERING,
    CAR_EXITING,
    CAR_ENTERED,
    CAR_EXITED,
    DISPLAY_SLOTS,
    VEHICLE_PROCESSING
};

State currentState = IDLE;

void setup() {
    mymotor.attach(8); 

    pinMode(IR1_Pin, INPUT);
    pinMode(IR2_Pin, INPUT);
    pinMode(slot1_Pin, INPUT);
    pinMode(slot2_Pin, INPUT);
    pinMode(slot3_Pin, INPUT);
    pinMode(slot4_Pin, INPUT);
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.setCursor(5, 0);
    lcd.print("Smart");
    lcd.setCursor(4, 1);
    lcd.print("Parking");
    delay(3000);
    moveServo(0);
    lcd.clear();
}

void loop() {
    bool IR1 = digitalRead(IR1_Pin) == LOW; // LOW means car is present
    bool IR2 = digitalRead(IR2_Pin) == LOW;

    switch (currentState) {
    case IDLE:
        if (IR1) {
            currentState = VEHICLE_PROCESSING;
        } else if (IR2) {
            currentState = VEHICLE_PROCESSING;
        } else {
            displayParkingSlots();
            delay(1000); // Display slots status refreshes every second
            currentState = DISPLAY_SLOTS;
        }
        break;
case VEHICLE_PROCESSING:
    if(IR1 && (digitalRead(slot1_Pin) == HIGH || digitalRead(slot2_Pin) == HIGH || digitalRead(slot3_Pin) == HIGH || digitalRead(slot4_Pin) == HIGH)) {
        // Move servo if a vehicle is entering and a slot is free

        lcd.clear();
        lcd.print("Car Entering");
        moveServo(90);
        // delay during the servo movement
        lcd.clear();
        lcd.print("Car Entered");
        delay(1000); // Additional delay to keep the message on the screen
        currentState = CAR_ENTERED;
    } else if(IR2) {
        // Move servo if a vehicle is exiting
        lcd.clear();
        lcd.print("Car Exiting");
        moveServo(90);
        // delay during the servo movement
        lcd.clear();
        lcd.print("Car Exited");
        delay(1000); // Additional delay to keep the message on the screen
        currentState = CAR_EXITED;
    } else {
        lcd.clear();
        lcd.print("Waiting");
        currentState = IDLE;
    }
    break;

    case CAR_ENTERED:
    case CAR_EXITED:
        delay(2000); // Wait for two seconds
        currentState = IDLE;
        break;
    case DISPLAY_SLOTS:
        currentState = IDLE;
        break;
}

delay(200); // Main loop delay
}

void moveServo(int angle){
  for(int i =0; i<=angle;i++){
    mymotor.write(i);
    delay(15);
  }
  delay(2000);
  for(int i=angle; i>=0;i--){
    mymotor.write(i);
    delay(15);
  }
}



void displayParkingSlots() {
lcd.clear();
lcd.print("S1:");
displaySlotStatus(slot1_Pin);
lcd.print(" S2:");
displaySlotStatus(slot2_Pin);
lcd.setCursor(0, 1); // Move to the second line
lcd.print("S3:");
displaySlotStatus(slot3_Pin);
lcd.print(" S4:");
displaySlotStatus(slot4_Pin);
}

void displaySlotStatus(int pin) {
if (digitalRead(pin) == LOW) {
// Slot is full
lcd.print("F");
} else {
lcd.print("E");
}
}


