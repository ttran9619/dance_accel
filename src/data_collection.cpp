/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Alek E., Tyler T.
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/

#include "serial/serial.h"

#include "thread_sharing.hpp"

#include <stdio.h>
#include <memory>
#include <iostream>

using namespace std;

/*-----------------------------------------------------------------
-                       Literal Constants
-----------------------------------------------------------------*/
#define PORT_SENSOR0 "/dev/tty.wchusbserial14510"
#define PORT_SENSOR1 "/dev/tty.wchusbserial1450"

#define BAUD_RATE       115200

/*-----------------------------------------------------------------
-                           Enumerations
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Structures
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
-                          Prototypes
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                          Procedures
-----------------------------------------------------------------*/
void data_collection_entry( sample_queue_t* queue )
{

    serial::Serial ard0( PORT_SENSOR0,
                         BAUD_RATE,
                         serial::Timeout::simpleTimeout( 1000 ) );
    if( !ard0.isOpen() )
    {
        cout << "Connection Failed!" << endl;
        exit( -1 );
    }
    cout << "Connection Sucessful!" << endl;

    // serial::Serial ard1( PORT_SENSOR0,
    //                      BAUD_RATE,
    //                      serial::Timeout::simpleTimeout( 1000 ) );
    // serial::Serial sen1( PORT_SENSOR0,
    //                      BAUD_RATE,
    //                      serial::Timeout::simpleTimeout( 1000 ) );

    sample_t c_data;

    for(;;)
    {
        ard0.read( (uint8_t*)&c_data.ard0, sizeof( sensor_data_t ) );
        //ard0.read( (uint8_t*)&c_data.sen1, sizeof( sensor_data_t ) );
        cout << "ACCEL0: " << c_data.ard0.a_mag0 << endl;
        cout << "ACCEL1: " << c_data.ard0.a_mag1 << endl;
        // ard1.read( (uint8_t*)&c_data.sen2, sizeof( sensor_data_t ) );
        // ard1.read( (uint8_t*)&c_data.sen3, sizeof( sensor_data_t ) );

        queue->push( c_data );
    };

}