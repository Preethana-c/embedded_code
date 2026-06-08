#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"

#define BUTTON_PIN 4
bool lastState = HIGH;

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHAR_UUID_TX  "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"  // Button → LED

BLEServer* pServer;
BLECharacteristic* pTxCharacteristic;

class ServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("✅ LED Connected!");
  }
};

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  BLEDevice::init("BUTTON_Controller");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());
  
  BLEService* pService = pServer->createService(SERVICE_UUID);
  
  pTxCharacteristic = pService->createCharacteristic(
    CHAR_UUID_TX,
    BLECharacteristic::PROPERTY_NOTIFY
  );
  pTxCharacteristic->addDescriptor(new BLE2902());
  
  pService->start();
  pServer->getAdvertising()->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  
  Serial.println("📡 Button Controller advertising...");
  Serial.println("Press button to test BLE");
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == LOW && lastState == HIGH) {  // Press edge
    Serial.println("🔘 BUTTON PRESSED - Sending via BLE");
    
    pTxCharacteristic->setValue("TOGGLE");
    pTxCharacteristic->notify();  // Send to LED
    
    delay(200);  // Simple debounce
  }
  
  lastState = buttonState;
  delay(50);
}