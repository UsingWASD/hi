#include <Wire.h>
#include <Servo.h>

const int MPU = 0x68;
const int servo_pin = 3;

int16_t x, y, z;
double wantangle;
Servo spinny;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  spinny.attach(servo_pin);
  
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  xyz();
  double angle = -atan2(x, z) * 180.0 / PI;
  double adjustment;
  double servoAngle;
  
  Serial.print("Angle: ");
  Serial.println(angle);
  Serial.print("x: "); Serial.println(x);
  Serial.print("y: "); Serial.println(y);
  Serial.print("z: "); Serial.println(z);
  
  if(angle == 90){
    servoAngle = 90 + wantangle;
  }
  else if(angle > 0) {
    adjustment = angle; // cw
    servoAngle = 90 + wantangle - adjustment;
  }
  else {
    adjustment = -angle; // ccw
    servoAngle = 90 + wantangle + adjustment;
  }
  Serial.print("adjustment angle: ");
  Serial.println(adjustment);

  servoAngle = constrain(servoAngle, 0, 180);
  spinny.write(servoAngle);

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
