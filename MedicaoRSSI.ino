//library
#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEUtils.h>

//variable
int rssi;
String mac;
BLEScan *scan;
int pino [] = {15, 4, 5, 19};

void setup() 
{
  Serial.begin(115200);
  BLEDevice::init("Scan Beacon");
  for(int i = 0; i <4; i++)
  {
    pinMode(pino[i],OUTPUT);
    delay(500);
      
  }
}

void loop()
{
  scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  BLEScanResults results = scan->start(1,false);
  if(results.getCount() > 0)
  {  
    BLEAdvertisedDevice device = results.getDevice(1);

    mac = device.getAddress().toString().c_str();
    if(mac.equals("ef:42:85:b6:07:e9"))
    {
      rssi = device.getRSSI();
      Serial.println(rssi);
      rssi > -80 ? digitalWrite(pino[0], 1): digitalWrite(pino[0], 0);
      rssi > -70 ? digitalWrite(pino[1], 1): digitalWrite(pino[1], 0);
      rssi > -50 ? digitalWrite(pino[2], 1): digitalWrite(pino[2], 0);
      rssi > -40 ? digitalWrite(pino[3], 1): digitalWrite(pino[3], 0);
    }
  }
}
