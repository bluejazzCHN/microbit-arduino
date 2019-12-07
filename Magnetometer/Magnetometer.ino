#include "Wire.h"
#include <SparkFun_MAG3110.h>
#include <Adafruit_Microbit.h>

Adafruit_Microbit_Matrix microbit;
MAG3110 compass = MAG3110();  // The compass chip
int baseline = 0;             

void setup() {
  microbit.begin();
  compass.initialize();       // Initializes the compass chip
  compass.start();            // Puts the sensor in active mode
  baseline = readStrength();  // Take a baseline reading of magnetic strength
  delay(500);

}

void loop() {
  microbit.show(String(abs(readStrength() - baseline)));
  delay(1000);
}

int readStrength() {
  int x, y, z;
  while(!compass.dataReady()) {};   // Wait for data to become available to read
  compass.readMag(&x, &y, &z);      // Read data into variables
  // calculate the RMS power combining x, y and z readings
  int power = sqrt((sq(float(x)) + sq(float(y)) + sq(float(z))) / 3);
  return power;
}
