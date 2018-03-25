/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Alek E., Tyler T.
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/
#include "AudioFile.h"
#include "audio_driver.hpp"

#include <vector>
#include <iostream>
#include <memory>

/*-----------------------------------------------------------------
-                       Literal Constants
-----------------------------------------------------------------*/
#define CHANNEL1 0
#define CHANNEL2 1
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
uptr_dv_t audio_driver()
{
AudioFile<double> audioFile;
audioFile.load ("/mnt/d/HackISUSpring2018/dance_accel/sound/abba.wav");

int sampleRate = audioFile.getSampleRate();
int bitDepth = audioFile.getBitDepth();

int lengthInSeconds = audioFile.getLengthInSeconds();

// or, just use this quick shortcut to print a summary to the console
audioFile.printSummary();

double sensitivity = 0;

double eLeft = 0;
double eRight = 0;

double ELeft = 0;
double ERight = 0;


int numSamples = audioFile.getNumSamplesPerChannel();
numSamples = (numSamples/44100)*44100;

int instantLength = numSamples/1024;

std::vector<double> instantEnergy(instantLength);
std::vector<double> averageEnergy(lengthInSeconds);
uptr_dv_t beats = std::make_unique<std::vector<bool>>(instantLength);

for (int i = 0; i < numSamples; i=i+1024)
{
	eLeft = 0;
	eRight = 0;
	for(int j = 0; j < 1024; j++) 
	{
		eLeft += audioFile.samples[CHANNEL1][i+j]*audioFile.samples[CHANNEL1][i+j];
		eRight += audioFile.samples[CHANNEL2][i+j]*audioFile.samples[CHANNEL2][i+j];
	}
	instantEnergy[i/1024] = eLeft + eRight;
	
	
}

for (int i = 0; i < numSamples; i=i+44100)
{
	ELeft = 0;
	ERight = 0;
	for(int j = 0; j < 44100; j++) 
	{
		ELeft += audioFile.samples[CHANNEL1][i+j]*audioFile.samples[CHANNEL1][i+j];
		ERight += audioFile.samples[CHANNEL2][i+j]*audioFile.samples[CHANNEL2][i+j];
	}
	averageEnergy[i/44100] = 1024*(ELeft+ERight)/44100;
}

for (int i = 0; i < 43; i++)
{
	sensitivity += (instantEnergy.at(i+20*43)-averageEnergy.at(20))*(instantEnergy.at(i+20*43)-averageEnergy.at(20));
}
sensitivity = sensitivity/4;

for (int i = 0; i < instantEnergy.size(); i++)
{
	double rhs = (averageEnergy[i/1024]);
	double lhs = instantEnergy[i];
	if( lhs > rhs )
	{
		(*beats)[i] = true;
	} 
	else 
	{
		(*beats)[i] = false;
	}
	
}

return std::move( beats );
}

