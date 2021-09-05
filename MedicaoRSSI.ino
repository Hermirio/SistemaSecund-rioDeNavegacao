//library
#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>

//variable
int rssi;

void setup() 
{
  Serial.begin(115200);
  BLEDevice::init("");
}

void loop()
{
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  BLEScanResults results = scan->start(1);
  for(int i = 0; i < results.getCount(); i++)
  {
    BLEAdvertisedDevice device = results.getDevice(i);
    rssi = device.getRSSI();
    Serial.print("Sinal: ");
    Serial.println(rssi);
  }
  
}
