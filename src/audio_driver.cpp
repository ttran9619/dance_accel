/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Alek E., Tyler T.
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/
#include "AudioFile.h"
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
void audio_driver()
{
AudioFile<double> audioFile;
audioFile.load ("~/Downloads/Abba - Dancing Queen.wav");

int sampleRate = audioFile.getSampleRate();
int bitDepth = audioFile.getBitDepth();

int numSamples = audioFile.getNumSamplesPerChannel();
double lengthInSeconds = audioFile.getLengthInSeconds();

int numChannels = audioFile.getNumChannels();
bool isMono = audioFile.isMono();
bool isStereo = audioFile.isStereo();

// or, just use this quick shortcut to print a summary to the console
audioFile.printSummary();

int channel = 0;
int numSamples = audioFile.getNumSamplesPerChannel();

for (int i = 0; i < numSamples; i++)
{
	double currentSample = audioFile.samples[channel][i];
}

}