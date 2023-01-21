#ifndef COMM_BLOCK_H
#define COMM_BLOCK_H

#include "Frame.h"
#include "Config.h"


class CommBlock
{
    
    public:

    CommBlock(const CrcBlock& crc, Config& simConfig, userSide externSide):frame(crc, simConfig,externSide) 
    {
       // frame.setFrame(crc, simConfig,externSide); 
       // hamming.setHamming(simConfig,externSide);
        simConfig.totalLength = simConfig.numFrames; // određuje se dužina Hemingovog koda i upisuje u Config strukturu
    }

    Frame frame;


};

#endif