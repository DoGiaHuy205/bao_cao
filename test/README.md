```
#include "BLEDevice.h"

#define LED_PIN 8
#define RECEIVE_LAZE 3
#define LED 5
int check = 0;

static BLEUUID serviceUUID("0000ffe0-0000-1000-8000-00805f9b34fb");
static BLEUUID characteristicUUID("0000ffe1-0000-1000-8000-00805f9b34fb");

static boolean doConnect = false;
static boolean connected = false;

static BLEAddress *pServerAddress;
static BLERemoteCharacteristic* pRemoteCharacteristic;
BLEClient* pClient;

class MyClientCallback : public BLEClientCallbacks {
public:
  // Override phương thức onConnect nếu nó là pure virtual trong lớp BLEClientCallbacks
  void onConnect(BLEClient* pClient) override {
    Serial.println("Connected to server");
  }

  // Override phương thức onDisconnect như đã có
  void onDisconnect(BLEClient* pClient) override {
    Serial.println("Disconnected from server");
    connected = false;
    doConnect = false;
  }
};

bool connectToServer(BLEAddress pAddress) {
  pClient = BLEDevice::createClient();
  pClient->setClientCallbacks(new MyClientCallback());

  pClient->connect(pAddress);
  
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    return false;
  }

  pRemoteCharacteristic = pRemoteService->getCharacteristic(characteristicUUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.print("Failed to find our characteristic UUID");
    return false;
  }
  Serial.println("Found our characteristic");

  pRemoteCharacteristic->registerForNotify(notifyCallback);
  return true;
}

static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  String receivedData = "";
  for (size_t i = 0; i < length; i++) {
    receivedData += (char)pData[i];
  }
  Serial.print("Received data: ");
  Serial.print(receivedData);

  if(strcmp(receivedData,"shoot") == 0){
    check++;
    Serial.println(check);
    int read1 = digitalRead(RECEIVE_LAZE);
    delay(500);
    int read2 = digitalRead(RECEIVE_LAZE);
    if(read1 == 0 && read2 == 0 && check <= 2){
      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW);
      
      Serial.println("shoot completed");
    }
    else{
      Serial.println("shoot failed");
    }
  }
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
      advertisedDevice.getScan()->stop();
      pServerAddress = new BLEAddress(advertisedDevice.getAddress());
      doConnect = true;
      Serial.println("Device found. Connecting!");
    }
  }
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  pinMode(RECEIVE_LAZE, INPUT);

  Serial.println("Starting BLE Client application...");
  BLEDevice::init("");

  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);
}

void loop() {
  if (doConnect) {
    if (connectToServer(*pServerAddress)) {
      Serial.println("We are now connected to the BLE Server.");
      connected = true;
    } else {
      Serial.println("Failed to connect to the server.");
    }
  }
  else {
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->start(30);
  }
  if (connected) digitalWrite(LED_PIN, LOW);
  else           digitalWrite(LED_PIN, HIGH);
}
```