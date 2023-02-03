#ifndef CONFIG_H
#define CONFIG_H


// struktura za konfigurisanje simulacije

struct Config 
{
    //parametri izvora
    const double transProb01 = 0.2;
    const double transProb10 = 0.5;
    const int sourceStreamSize = 4000000;
    const int payloadSize = 40;
    int numFrames = sourceStreamSize/payloadSize;

    // parametri crc bloka
	const int crcGenPoly[17] = { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 };
    const int overheadSize = sizeof(crcGenPoly)/sizeof(int)-1;
    const int frameLength = numFrames*(payloadSize+overheadSize);
    int totalLength;

    // parametri kanala
	const double bscErrorProbArray[1] = { 0.07 };
    const int numOfChannels = sizeof(bscErrorProbArray)/sizeof(double);
};

enum userSide{transmit, receive};

#endif
