/**************************************************************************/
/*!

    @author   Valery Smith
    @license  BSD (see license.txt)

    This is to get accelerometer data to manipulate
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  Serial.begin(115200);
  
    if (! mma.begin()) {
      Serial.println("Couldnt start");
      while (1);
    }
    //Serial.println("MMA8451 found!");

  mma.setRange(MMA8451_RANGE_2_G);
  //Serial.print("Range = "); Serial.print(2 << mma.getRange());
  ///Serial.println("G");
}
float r = 0;
unsigned long ntime = 0;
unsigned long otime = 0;
void loop() {
  // Read the 'raw' data in 14-bit counts

  mma.read();
  /*
  Serial.print("X:\t"); Serial.print(mma.x);
  Serial.print("\tY:\t"); Serial.print(mma.y);
  Serial.print("\tZ:\t"); Serial.print(mma.z);
  Serial.println();*/

  /* Get a new sensor event */
  sensors_event_t event;
  mma.getEvent(&event);

  /* Display the results (acceleration is measured in m/s^2)
    Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
    Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
    Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");*/
  r = sqrt(sq(event.acceleration.x) + sq(event.acceleration.y) + sq(event.acceleration.z));
  Serial.println(r);

  ntime = millis();
  if ((ntime - otime) >= 500) {
    otime = ntime;
    Serial.println(r);
  }

  /* Get the orientation of the sensor */

  //Serial.println();


}
