#ifndef CHANNEL_H
#define CHANNEL_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Channel
{
    double channelRate;
    int channelSequnceLength;
    int* output;  
    int* outputCopy;

    void insertErrors();
	//ulaz u kanal se baferiše
    void fillChannel(int* sequence) {for(int i=0;i<channelSequnceLength;i++) output[i]=sequence[i];} 

    public:

    Channel(int length,double rate=0): 
		channelRate(rate), channelSequnceLength(length)
	{output = new int[channelSequnceLength];  outputCopy = new int[channelSequnceLength];};
    ~Channel() {delete[] output; delete[] outputCopy;}
    void fillAndProcess(int*);
    void setChannelRate(double rate) {channelRate = rate;}
    int* getOutput() {return outputCopy;}
};

#endif
