#include <picobricks.h>
#include <Wire.h>

#define MIN 10
#define MID 90
#define MAX 170

APDS9960 apds;
motorDriver motor;

int panAngle = 90;
int tiltAngle = 90;
int pan = 1;
int tilt = 1;
int gesture = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(); 

  apds.init(GESTURE);
  motor.servo(1, panAngle);
  motor.servo(3, tiltAngle);
}

void loop() {
  gesture = apds.readGesture();
 
  if (gesture == UP){
    tilt++;
  }
 else if(gesture == DOWN){
    tilt--;
  }
  else if(gesture == LEFT){
    pan++;
  }
  else if(gesture == RIGHT){
    pan--;
  }

  if(tilt >=2)
    tilt = 2;

  if(tilt <=0)
    tilt = 0;

  if(pan >=2)
    pan = 2;

  if(pan <=0)
    pan = 0;

  if (tilt == 1)
    tiltAngle = MID;
  else if (tilt == 0)
    tiltAngle = MIN;
  else
    tiltAngle = MAX;

  if (pan == 1)
    panAngle = MID;
  else if (pan == 0)
    panAngle = MIN;
  else
    panAngle = MAX;

  motor.servo(1, panAngle);
  motor.servo(3, tiltAngle);

  delay(500);
}