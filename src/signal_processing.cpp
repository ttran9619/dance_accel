/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Alek E., Tyler T.
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/
#include "thread_sharing.hpp"
#include "audio_driver.hpp"

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

/* 
 
 LEDS go from 0-32
 LEDS from 0-8 are determined by how close they are to 25.
	*/
	
void signal_processing_entry( sample_queue_t* queue )
{
	uptr_dv_t* beats;
	
	uint8_t ledVal = 0;
	auto leifs_le = []( uint8_t aData )
		{
			if(aData <= 15) 
			{
				aData = 0;
			}
			else if(aData > 15 && aData < 25)
			{
				aData = 1;
			} 	
			else 
			{
				aData = 32-aData;
			}
			return aData;
		};
	auto beat_le = [ beats ]( uint8_t aData )
		{
			if (aData == 1) 
			{
				//TODO
			}
			
			return aData;
		};	
		
	// press space to start
	while(true) 
	{
		sample_t sampleData = queue->pop();
		uint8_t data1 = sampleData.ard0.a_mag0;
		uint8_t data2 = sampleData.ard0.a_mag1;
		uint8_t data3 = sampleData.ard1.a_mag0;
		uint8_t data4 = sampleData.ard1.a_mag1;
		
		
		data1 = leifs_le( data1 );
		data2 = leifs_le( data2 );
		data3 = leifs_le( data3 );
		data4 = leifs_le( data4 );
		
		
		
		uint8_t combData = data1 + data2 + data3 + data4;
		if(data1 > 1 || data2 > 1 || data3 > 1 || data4 > 1)
		{
			uint8_t tempMax1 = max(data1,data2);
			uint8_t tempMax2 = max(data3,data4);
			ledVal = max(tempMax1,tempMax2);
		} 
		else if(combData != 0)
		{
			
		}
		
		
	}
	
}

