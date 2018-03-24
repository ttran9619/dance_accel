/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Alek E., Tyler T.
-----------------------------------------------------------------*/
#ifndef THREAD_SHARING_H
#define THREAD_SHARING_H

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/
#include "threaded_queue.hpp"

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
class Sample;

/*-----------------------------------------------------------------
-                             Structs
-----------------------------------------------------------------*/
extern "C"
{
    typedef struct sensor_data_struct
    {
        float a_mag0;
        float a_mag1;
    } sensor_data_t;

    typedef struct sample
    {
        sensor_data_t sen0;
        sensor_data_t sen1;
        sensor_data_t sen2;
        sensor_data_t sen3;
    } sample_t;
};

/*-----------------------------------------------------------------
-                             Typedefs
-----------------------------------------------------------------*/
typedef ThreadedQueue<sample_t> sample_queue_t;

/*-----------------------------------------------------------------
-                             Functors
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                             Classes
-----------------------------------------------------------------*/
struct InputQueues
{
    sample_queue_t accel0;
    sample_queue_t accel1;
    sample_queue_t accel2;
    sample_queue_t accel3;
};

/*-----------------------------------------------------------------
-                             Prototypes
-----------------------------------------------------------------*/
void data_collection_entry( sample_queue_t* queue );
void signal_processing_entry( sample_queue_t* queue );

#endif