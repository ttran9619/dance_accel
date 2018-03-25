#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

/* Literials */
#define SAMPLING_PERIOD 1

/* Structures */
typedef struct sensor_data_struct
{
    unsigned char a_mag0;
    unsigned char a_mag1;
} sensor_data_t;

/* Globals */
Adafruit_MMA8451 mma0 = Adafruit_MMA8451();
Adafruit_MMA8451 mma1 = Adafruit_MMA8451();

unsigned long otime = 0;

sensor_data_t curr_samp;

/* Procedures */
void setup() 
{
  Serial.begin( 115200 );
  
  if ( !mma0.begin( 0x1D ) ) 
  {
    Serial.println( "Couldn't start MMA1" );
    while( 1 ){};
  }

  if ( !mma1.begin( 0x1C ) ) 
  {
    Serial.println( "Couldn't start MMA1" );
    while( 1 ){};
  }

  mma0.setDataRate(MMA8451_DATARATE_800_HZ);
  mma1.setDataRate(MMA8451_DATARATE_800_HZ);
}

void loop() 
{
  otime = millis();
  /* Get a new sensor events */
  sensors_event_t event0;
  mma0.getEvent( &event0 );

  sensors_event_t event1;
  mma1.getEvent( &event1 );

  /* Populate output packet */
  curr_samp.a_mag0 = sqrt( sq( event0.acceleration.x ) + 
                           sq( event0.acceleration.y ) + 
                           sq( event0.acceleration.z ) );

  curr_samp.a_mag1 = sqrt( sq( event1.acceleration.x ) + 
                           sq( event1.acceleration.y ) + 
                           sq( event1.acceleration.z ) );

  /* Send off Data */
  Serial.write( (char*)&curr_samp, sizeof( sensor_data_t ) );               

  /* Wait until the sampling period is over */
  while ( ( millis() - otime ) < SAMPLING_PERIOD ) 
  {
  }
}
