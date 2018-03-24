/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Alek E., Tyler T.
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/
#include "AudioFile.h"

#include <vector>
/*-----------------------------------------------------------------
-                       Literal Constants
-----------------------------------------------------------------*/
#define CHANNEL1 0
#define CHANNEL2 1
#define SENSITIVITY 0.67
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
void audio_driver()
{
AudioFile<double> audioFile;
audioFile.load ("/home/pi/Downloads/abba.wav");

int sampleRate = audioFile.getSampleRate();
int bitDepth = audioFile.getBitDepth();

double lengthInSeconds = audioFile.getLengthInSeconds();

// or, just use this quick shortcut to print a summary to the console
audioFile.printSummary();

double eLeft = 0;
double eRight = 0;

double ELeft = 0;
double ERight = 0;


int numSamples = audioFile.getNumSamplesPerChannel();
numSamples = (numSamples/44100)*44100;

int instantLength = numSamples/1024;

std::vector<double> instantEnergy(instantLength);
std::vector<double> averageEnergy(lengthInSeconds);
std::vector<bool> beats(instantLength);

for (int i = 0; i < numSamples; i=i+1024)
{
	for(int j = 0; j < 1024; j++) 
	{
		eLeft += audioFile.samples[CHANNEL1][i+j]*audioFile.samples[CHANNEL1][i+j];
		eRight += audioFile.samples[CHANNEL2][i+j]*audioFile.samples[CHANNEL2][i+j];
	}
	instantEnergy[i/1024] = eLeft + eRight;
	
	
}

for (int i = 0; i < numSamples; i=i+44100)
{
	for(int j = 0; j < 1024; j++) 
	{
		ELeft += audioFile.samples[CHANNEL1][i+j]*audioFile.samples[CHANNEL1][i+j];
		ERight += audioFile.samples[CHANNEL2][i+j]*audioFile.samples[CHANNEL2][i+j];
	}
	averageEnergy[i/44100] = 1024*(ELeft+ERight)/44100;
}

for (int i = 0; i < instantEnergy.size(); i++)
{
	if(instantEnergy[i] > averageEnergy[i/44100]*SENSITIVITY)
	{
		beats[i] = true;
	} 
	else 
	{
		beats[i] = false;
	}
}
}

