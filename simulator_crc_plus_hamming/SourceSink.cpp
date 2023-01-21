#include "SourceSink.h"


void SourceSink::generateStream() // binarni izvor s memorijom prvog reda
{
    double randomNumber;
    int sourceState = 0;
    
    srand(time(nullptr));                // podesiti seed slučajnog generatora na osnovu trenutnog vremena; 
                                         // srand(const) omogućava ponovljivost niza slučajnog brojeva 

    for (int i=0;i<sourceStreamSize;i++)
    {
        randomNumber = double(rand())/RAND_MAX;

        switch (sourceState)
        {
        case 0:
            sourceState = 1-int(randomNumber>transProb01);
            output[i]=sourceState;
            break;
  
        default: 
            sourceState = 1-int(randomNumber<transProb10);
            output[i]=sourceState;
        }
    }

    for (int i=0;i<sourceStreamSize;i++) outputCopy[i] = output[i];  //kopiranje niza za izlaz
}

void SourceSink::calculateErrors(const Config& myConfig, int* receivedframes)
{
    int numUndetecdedErrors = 0;

    for (int i=0;i<myConfig.numFrames;i++)
    {
        if(receivedframes[i*myConfig.payloadSize]!=2)
        {
            for (int j=0;j<myConfig.payloadSize;j++) 
            {
                if(receivedframes[i*myConfig.payloadSize+j]!=output[i*myConfig.payloadSize+j])
                { 
                    numUndetecdedErrors ++;
                    break;
                }
            }
  
        }
    }
    
    cout << "Num. erroneous frames: " << numUndetecdedErrors << endl;
    cout << "--------------------------------------\n";

}