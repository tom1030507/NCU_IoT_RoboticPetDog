#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <SeeedOLED.h>
#include <DHT.h>

#define SS_PIN  5  // RFID SS pin
#define RST_PIN 27 // RFID reset pin

// Function declarations
void controlCarMovement(int rssi);
void moveMotors(bool m1, bool m2, bool m3, bool m4);
void moveForward();
void stopMotors();
void turnLeft();
bool checkRFID(MFRC522& rfid);
void updateOLED();

// Motor pins
const int motorPin1 = 25; // Left motor forward
const int motorPin2 = 26; // Left motor backward
const int motorPin3 = 32; // Right motor forward
const int motorPin4 = 33; // Right motor backward

// BLE and control settings
String beaconAddress = "12:3b:6a:1a:d2:07";
String myUID = "C6A9C5F9"; // RFID UID
int rssiThreshold = -60; // Proximity threshold
double scanTime = 10.0; // BLE scan duration
int lastRSSI = -100; // Last RSSI value
bool isCarActive = false, isBeaconFound = false;
BLEScan* pBLEScan;

// RFID and DHT22 setup
MFRC522 rfid(SS_PIN, RST_PIN);
DHT dht(15, DHT22);

// BLE callback class
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) override {
        String detectedAddress = advertisedDevice.getAddress().toString().c_str();

        if (detectedAddress == beaconAddress) {
            advertisedDevice.getScan()->stop();
            Serial.printf("Found Address: %s\n", detectedAddress.c_str());
            int beaconRSSI = advertisedDevice.getRSSI();
            Serial.printf("RSSI: %d\n", beaconRSSI);

            controlCarMovement(beaconRSSI);
        }
    }
};

void setup() {
    Serial.begin(115200);
    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);

    SPI.begin();
    dht.begin();
    Wire.begin();
    SeeedOled.init();
    SeeedOled.deactivateScroll();
    rfid.PCD_Init();

    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
}

void loop() {
    if (checkRFID(rfid)) {
        isCarActive = !isCarActive; // Toggle car state
        Serial.printf("Car state toggled: %s\n", isCarActive ? "ON" : "OFF");
    }

    if (isCarActive) {
        BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
        Serial.printf("Devices found: %d\n", foundDevices.getCount());
        pBLEScan->clearResults();
    } else {
        stopMotors();
    }

    updateOLED();
    delay(100);
}

void controlCarMovement(int rssi) {
    if (rssi < rssiThreshold) { // Far from beacon
        moveForward();
        if (lastRSSI != -100 && rssi <= lastRSSI) { // Moving away
            turnLeft();
        }
        isBeaconFound = false;
    } else { // Near beacon
        stopMotors();
        isBeaconFound = true;
    }
    lastRSSI = rssi;
}

void moveMotors(bool m1, bool m2, bool m3, bool m4) {
    digitalWrite(motorPin1, m1);
    digitalWrite(motorPin2, m2);
    digitalWrite(motorPin3, m3);
    digitalWrite(motorPin4, m4);
}

void moveForward() { moveMotors(HIGH, LOW, HIGH, LOW); }

void stopMotors() { moveMotors(HIGH, HIGH, HIGH, HIGH); }

void turnLeft() { moveMotors(HIGH, LOW, LOW, HIGH); }

bool checkRFID(MFRC522& rfid) {
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String uid = "";
        for (int i = 0; i < rfid.uid.size; i++) {
            if (rfid.uid.uidByte[i] < 0x10) uid += "0";
            uid += String(rfid.uid.uidByte[i], HEX);
        }
        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
        uid.toUpperCase(); 
        return uid == myUID;
    }
    
    return false;
}

void updateOLED() {
    float temp = round(dht.readTemperature() * 10) / 10.0;
    float humidity = round(dht.readHumidity() * 10) / 10.0;

    String status = isCarActive ? "ON" : "OFF";
    String message = isCarActive ? (isBeaconFound ? "I found!" : "Finding...")
                                 : (temp >= 28 ? "I'm HOT!"
                                               : (temp <= 23 ? "I'm COLD!" : "Hi, master!"));

    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0, 0); SeeedOled.putString("Status : "); SeeedOled.putString(status.c_str());
    SeeedOled.setTextXY(1, 0); SeeedOled.putString("Temp   : "); SeeedOled.putFloat(temp); SeeedOled.putString("'C");
    SeeedOled.setTextXY(2, 0); SeeedOled.putString("Humid  : "); SeeedOled.putFloat(humidity); SeeedOled.putString("%");
    SeeedOled.setTextXY(3, 0); SeeedOled.putString("Message:");
    SeeedOled.setTextXY(4, 0); SeeedOled.putString(message.c_str());
}
