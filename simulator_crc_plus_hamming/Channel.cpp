#include "Channel.h"



void Channel::insertErrors()
{

    double randomNumber;
    
    srand(time(nullptr));                // podesiti seed slučajnog generatora na osnovu trenutnog vremena; srand(const) omogućava ponovljivost niza slučajnog brojeva 

    for (int i=0;i<channelSequnceLength;i++)
    {
        randomNumber = double(rand())/RAND_MAX;
        
        if(randomNumber<channelRate) output[i] = (output[i]+1)%2; 
    } 
}


void Channel::fillAndProcess(int* sequence) 
{
    fillChannel(sequence); // baferiše se ulaz u kanal

    insertErrors();  // dodaju se greške

    for(int i=0;i<channelSequnceLength;i++) outputCopy[i] = output[i]; // pravi se kopija za izlaz

    
}