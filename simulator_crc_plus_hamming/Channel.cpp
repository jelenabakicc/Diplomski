#include "Channel.h"

void Channel::insertErrors()
{

    double randomNumber;
	// podesiti seed slučajnog generatora na osnovu trenutnog vremena; 
	// srand(const) omogućava ponovljivost niza slučajnog brojeva 
    srand(time(nullptr));                

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

	// pravi se kopija za izlaz
    for(int i=0;i<channelSequnceLength;i++) outputCopy[i] = output[i];     
}

