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
#include <string>

using namespace std;

/*-----------------------------------------------------------------
-                       Literal Constants
-----------------------------------------------------------------*/
#define PORT_SENSOR0 "/dev/tty.wchusbserial14510"
#define PORT_SENSOR1 "/dev/tty.wchusbserial1450"

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
void data_collection_entry( sample_queue_t* queue, std::string port0, std::string port1 )
{

    serial::Serial ard0( port0,
                         BAUD_RATE,
                         serial::Timeout::simpleTimeout( 1000 ) );
    if( !ard0.isOpen() )
    {
        cout << "Connection Failed!" << endl;
        exit( -1 );
    }
    cout << "Connection Sucessful!" << endl;

    // serial::Serial ard1( port1,
    //                      BAUD_RATE,
    //                      serial::Timeout::simpleTimeout( 1000 ) );
    // if( !ard1.isOpen() )
    // {
    //     cout << "Connection Failed!" << endl;
    //     exit( -1 );
    // }
    // cout << "Connection Sucessful!" << endl;

    sample_t c_data;
    for(;;)
    {
        ard0.read( (uint8_t*)&c_data.ard0, sizeof( sensor_data_t ) );
        //ard1.read( (uint8_t*)&c_data.ard1, sizeof( sensor_data_t ) );
        cout << "ACCEL0: " << std::to_string( c_data.ard0.a_mag0 ) << "  ACCEL1: " << std::to_string( c_data.ard0.a_mag1 ) << endl;

        queue->push( c_data );
    };

}