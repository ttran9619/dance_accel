/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Alek E., Tyler T.
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/
#include "threaded_queue.hpp"
#include "thread_sharing.hpp"
#include "LEDOut.hpp"

#include <thread>
#include <string>
#include <iostream>

/*-----------------------------------------------------------------
-                       Literal Constants
-----------------------------------------------------------------*/

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
int main( int argc, char* argv[] )
{
    /* Setup Devices */
    sample_queue_t queue;

    if( 4 != argc )
    {
        std::cout << "    Error: Program takes 3 args!" << std::endl;
        exit( -1 );
    }

    /* Call Audio Setup Code */

    /* Wait for user start signal */
    std::string input;
    while( 0 != input.compare( "Start" ) )
    {
        std::cout << "Waiting for Start, enter \"Start\"";
        std::cin >> input;
    }

    LEDOut output( argv[3] );

    output.write( 1 );

    while(true);

    /* Instantiate Threads */
    std::thread thread_dc( data_collection_entry, &queue, std::string( argv[1] ), std::string( argv[2] ) );

    //std::thread thread_ps( signal_processing_entry, &queue, std::string( argv[3] ) );

    thread_dc.join();
    //thread_ps.join();

    return 0;
}