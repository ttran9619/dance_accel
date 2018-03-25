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

    if( 5 != argc )
    {
        std::cout << "  Error: Program takes 4 args!" << std::endl;
        std::cout << "  Args: [AccelArduino0] [AccelArduino1] [OutputArduino0] [Soundfile]" << std::endl;
        std::cout << "  Args must be absolute paths to the devices/files" << std::endl;
        exit( -1 );
    }

    /* Call Audio Setup Code */
    std::cout << "Processing Sound File";
    uptr_dv_t audio_data = audio_driver( std::string( argv[4] ) );

    /* Wait for user start signal */
    std::string input;
    while( 0 != input.compare( "Start" ) )
    {
        std::cout << "Waiting for Start, enter \"Start\"";
        std::cin >> input;
    }

    /* Instantiate Threads */
    std::thread thread_dc( data_collection_entry, &queue, std::string( argv[1] ), std::string( argv[2] ) );
    std::thread thread_ps( signal_processing_entry, &queue, std::move( audio_data ), std::string( argv[3] ) );

    thread_dc.join();
    thread_ps.join();

    return 0;
}