/*-----------------------------------------------------------------
-                           HackISU S2018
-              Valery S., Leif B., Alek E., Tyler T.
-----------------------------------------------------------------*/

/*-----------------------------------------------------------------
-                           Includes
-----------------------------------------------------------------*/
#include "AudioFile.h"
#include "
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
audioFile.load ("/home/pi/Downloads/abba.wav");

int sampleRate = audioFile.getSampleRate();
int bitDepth = audioFile.getBitDepth();

double lengthInSeconds = audioFile.getLengthInSeconds();

// or, just use this quick shortcut to print a summary to the console
audioFile.printSummary();

int channel = 0;

int numSamples = audioFile.getNumSamplesPerChannel();

for (int i = 0; i < numSamples; i++)
{
	double currentSample = audioFile.samples[channel][i];
}

}
