//library
#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEUtils.h>

//variable
int rssi;
BLEScan *scan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void setup() 
{
  Serial.begin(115200);
  BLEDevice::init("Scan Beacon");
}

void loop()
{
  scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  //scan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  BLEScanResults results = scan->start(1);
  for(int i = 0; i < results.getCount(); i++)
  {
    BLEAdvertisedDevice device = results.getDevice(i);
    rssi = device.getRSSI();
    Serial.print("Sinal RSSI: ");
    Serial.println(rssi);
  }
  
}
