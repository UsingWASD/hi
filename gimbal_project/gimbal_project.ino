#include <Wire.h>

const int MPU = 0x68;
int16_t x, y, z;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  xyz();
  double angle = atan2(x, z) * 180.0 / PI;
  
  Serial.print("Angle: ");
  Serial.println(angle);
  Serial.print("x"); Serial.println(x);
  Serial.print("y"); Serial.println(y);
  Serial.print("z"); Serial.println(z);
  

  delay(100);

}

void xyz() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU, 6,true);

  byte x_high = Wire.read();
  byte x_low  = Wire.read();
  byte y_high = Wire.read();
  byte y_low  = Wire.read();
  byte z_high = Wire.read();
  byte z_low  = Wire.read();
  
  x = (x_high * 256) + x_low;
  y = (y_high * 256) + y_low;
  z = (z_high * 256) + z_low;

}
