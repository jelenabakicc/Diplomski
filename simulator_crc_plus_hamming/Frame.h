#ifndef FRAME_H
#define FRAME_H

#include "CrcBlock.h"
#include "Config.h"

class Frame
{
    int numFrames;
    int payloadSize;
    int overheadSize;
    int numDetectedFailures;
    int* output;
    int* outputCopy;

    userSide side;

    CrcBlock crc;

    void checkFrames(int*);   // frejmovi se proveravaju i svi frejmovi sa detektovanom greškom se brišu (dodeljuje im se vrednost 2) 


    public:

    // konstruktori
    Frame();                    //inicijalizacija praznim blokom
    Frame(const CrcBlock&,const Config&,userSide);    // kompletna inicijalizacija 
    // destruktor
    ~Frame() {delete[] output; delete[] outputCopy;};

    void fillAndProcess(int*);          // napuniti frejmove bitima za slanje 
    int* getOutput() const {return outputCopy;}
    void setFrame(const CrcBlock&,const Config&,userSide);
    // ispis podataka o frejmovima
    void printFrameInfo() const;

};

#endif