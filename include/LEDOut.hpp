/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Emily A., Tyler T.
-----------------------------------------------------------------*/
#ifndef LED_OUT_H
#define LED_OUT_H

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/
#include "threaded_queue.hpp"
#include "audio_driver.hpp"

#include "serial/serial.h"

#include <string>
#include <iostream>

/*-----------------------------------------------------------------
-                        Literal Constants
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Enumerations
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Macros
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                        Forward Declarations
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Structs
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Typedefs
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Functors
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Classes
-----------------------------------------------------------------*/
class LEDOut
{
    public:
        LEDOut( std::string port )
            :out_dev( port,
                      BAUD_RATE,
                      serial::Timeout::simpleTimeout( 1000 ) )
        {
            if( !out_dev.isOpen() )
            {
                std::cout << "Connection Failed!" << std::endl;
                exit( -1 );
            }
            std::cout << "Connection Sucessful!" << std::endl;
        };

        ~LEDOut()
        {
            out_dev.close();
        };

        void set_led( uint8_t aVal )
        {
            std::string temp( std::to_string( aVal ) );
            temp += "\n";
            const char* temp_str = temp.c_str();
            out_dev.write( (const uint8_t*)temp_str, temp.size() );
            this->readline();
        };

        void readline()
        {
            std::cout << out_dev.readline() << std::endl;
        };

    private:
        serial::Serial out_dev;
};

/*-----------------------------------------------------------------
-                             Prototypes
-----------------------------------------------------------------*/

#endif