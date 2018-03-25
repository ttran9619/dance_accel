/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Alek E., Tyler T.
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/
#include "thread_sharing.hpp"
#include "audio_driver.hpp"
#include "LEDOut.hpp"

#include <chrono>
#include <string>

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


void signal_processing_entry( sample_queue_t* queue, uptr_dv_t audio_data, std::string port2 )
{
    LEDOut output( port2 );

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	long int time = 0;

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
	auto beat_le = [ &audio_data, time ]( uint8_t aData )
		{

			for(int i = 0; i < 125; i++)
			{
				if((time-i) >= 0 && (*audio_data)[time-i] == true)
				{
					return aData = 16;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-125) >= 0 && (*audio_data)[time-i-125] == true)
				{
					return aData = 15;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-250) >= 0 && (*audio_data)[time-i-250] == true)
				{
					return aData = 14;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-375) >= 0 && (*audio_data)[time-i-375] == true)
				{
					return aData = 13;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-500) >= 0 && (*audio_data)[time-i-500] == true)
				{
					return aData = 12;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-625) >= 0 && (*audio_data)[time-i-625] == true)
				{
					return aData = 11;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-750) >= 0 && (*audio_data)[time-i-750] == true)
				{
					return aData = 10;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-875) >= 0 && (*audio_data)[time-i-875] == true)
				{
					return aData = 9;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-1000) >= 0 && (*audio_data)[time-i-1000] == true)
				{
					return aData = 8;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-1125) >= 0 && (*audio_data)[time-i-1125] == true)
				{
					return aData = 7;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-1250) >= 0 && (*audio_data)[time-i-1250] == true)
				{
					return aData = 6;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-1375) >= 0 && (*audio_data)[time-i-1375] == true)
				{
					return aData = 5;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-1500) >= 0 && (*audio_data)[time-i-1500] == true)
				{
					return aData = 4;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-1625) >= 0 && (*audio_data)[time-i-1625] == true)
				{
					return aData = 3;
				}
			}
			for(int i = 0; i < 125; i++)
			{
				if((time-i-1800) >= 0 && (*audio_data)[time-i-1800] == true)
				{
					return aData = 2;
				}
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
        uint8_t ledVal;


		data1 = leifs_le( data1 );
		data2 = leifs_le( data2 );
		data3 = leifs_le( data3 );
		data4 = leifs_le( data4 );
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();


		time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		uint8_t combData = data1 + data2 + data3 + data4;
		if(data1 > 1 || data2 > 1 || data3 > 1 || data4 > 1)
		{
			uint8_t tempMax1 = std::max(data1,data2);
			uint8_t tempMax2 = std::max(data3,data4);
			ledVal = std::max(tempMax1,tempMax2);
		}
		else if(combData != 0)
		{
			if(data1 == 1)
			{
				data1 = beat_le( data1 );
				if(data2 == 1)
				{
					data2 = beat_le( data2 );
					data3 = 0;
					data4 = 0;
				}
				else
				{
					if(data3 == 1)
					{
						data3 = beat_le( data3 );
						data4 = 0;
					}
					else
					{
						if(data4 == 1)
						{
							data4 = beat_le( data4 );
						}
					}
				}
			}
			else
			{
				if(data2 == 1)
				{
					data2 = beat_le( data2 );
					if(data3 == 1)
					{
						data3 = beat_le( data3 );
						data4 = 0;
					}
				}
				else
				{
					if(data3 == 1)
					{
						data3 = beat_le( data3 );
						if(data4 == 1)
						{
							data4 = beat_le( data4 );
						}
					}
					else
					{
						if(data4 == 1)
						{
							data4 = beat_le( data4 );
						}
						else
						{
							data1 = 0;
							data2 = 0;
							data3 = 0;
							data4 = 0;
						}
					}
				}
			}
		}
        ledVal = data1+data2+data3+data4;
        output.set_led( ledVal );


	}

}

