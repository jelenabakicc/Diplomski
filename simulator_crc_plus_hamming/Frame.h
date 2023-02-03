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

	// frejmovi se proveravaju i svi frejmovi sa detektovanom 
	// greškom se brišu (dodeljuje im se vrednost 2) 
    void checkFrames(int*);   

    public:
    // konstruktori
	// inicijalizacija praznim blokom
    Frame();                    
	// kompletna inicijalizacija 
    Frame(const CrcBlock&,const Config&,userSide);   
    // destruktor
    ~Frame() {delete[] output; delete[] outputCopy;};

    void fillAndProcess(int*);   // napuniti frejmove bitima za slanje 
    int* getOutput() const {return outputCopy;}
    void setFrame(const CrcBlock&,const Config&,userSide);
    // ispis podataka o frejmovima
    void printFrameInfo() const;

};

#endif
