// code for just one sensor. short. sweet.

// libraries
#include <Wire.h>
#include <Adafruit_VL6180X.h>

// declaring the sensor
Adafruit_VL6180X tof = Adafruit_VL6180X();

void setup() {
  Serial.begin(9600); // serial monitor setup
  while (!Serial) delay(1);
  if (!tof.begin()) while (1); // sensor setup
  Serial.print("Sensor Found!");
}

void loop() {
  Serial.print("Dist (mm): ");
  Serial.println(tof.readRange()); // prints the distance
  delay(100); // wait 1/10th of a second
}
