// this code is different from the other examples in that is uses 3 sensors over the same line
// we basically run a sequence to reset their addresses then read
// i wrote this code long ago and i hate it now
// will modify and add another file to read them in a more adaptable modular way
// such that you dont have to write so much for just three sensors.

// required libraries
// #include <Wire.h>
#include <Adafruit_VL6180X.h>

// declaring 3 sensors
Adafruit_VL6180X sensorLeft = Adafruit_VL6180X(), sensorFront = Adafruit_VL6180X(), sensorRight = Adafruit_VL6180X();
const int sensorLeftSHDN = 11, sensorFrontSHDN = 12, sensorRightSHDN = 13; // shutdown pins of the sensors: used to init the setting of unique addresses
const int sensorLeftAddress = 0x30, sensorFrontAddress = 0x31, sensorRightAddress = 0x32; // addresses we will set

int leftDistance, rightDistance, frontDistance; // will update these in loop once addresses are set

void setup() {
  Serial.begin(115200); // serial monitor setup
  while (!Serial) delay(1);

  pinMode(sensorLeftSHDN,OUTPUT); pinMode(sensorFrontSHDN,OUTPUT); pinMode(sensorRightSHDN,OUTPUT); // shdn pins as output
  Serial.println(F("Serial ready, SHDN initiated.")); // debug text
  delay(1000); // wait 1 sec
  setSHDN(LOW,LOW,LOW); // set all shdn to low
  setAddress(); // run address setting function
  Serial.println(F("Address set.")); // debug text
  Serial.println(F("Setup completed.")); // ta-da!
}

void loop() {
  leftDistance = readSensor(sensorLeft), frontDistance = readSensor(sensorFront), rightDistance = readSensor(sensorRight);
  Serial.println("Left: " + (String)leftDistance + "  Front: " + (String)frontDistance + "  Right: " + (String)rightDistance);
  delay(100);
}



// returns reading from specified sensor
int readSensor(Adafruit_VL6180X &sensor) {
  return sensor.readRange();
}

void setAddress() {
  setSHDN(LOW,LOW,LOW); delay(10);
  setSHDN(HIGH,HIGH,HIGH); delay(10);

  setSHDN(HIGH,LOW,LOW); delay(10);
  if (!sensorLeft.begin()) while (1);
  sensorLeft.setAddress(sensorLeftAddress);
  delay(10);
  digitalWrite(sensorFrontSHDN,HIGH); delay(10);
  if (!sensorFront.begin()) while (1);
  sensorFront.setAddress(sensorFrontAddress);
  delay(10);
  digitalWrite(sensorRightSHDN,HIGH); delay(10);
  if (!sensorRight.begin()) while (1);
  sensorRight.setAddress(sensorRightAddress);
  delay(10);
}

// quick func to set state of 3 shdn pins at once
void setSHDN(int leftState, int frontState, int rightState) {
  digitalWrite(sensorLeftSHDN,leftState);
  digitalWrite(sensorFrontSHDN,frontState);
  digitalWrite(sensorRightSHDN,rightState);
}
