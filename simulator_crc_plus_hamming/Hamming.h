#ifndef HAMMING_H
#define HAMMING_H

#include <iostream>
#include <math.h>
#include <string>

#include "Config.h"

using namespace std;

class Hamming
{
    int infoLength;
    int codeLength;
    int numFrames;
    int* output;
    int *outputCopy;
    userSide side;

    int calculateCodeLength();
    int calculateParity(int*, int);
    int* encodeWord(int*);   // kodovanje info sekvence 
    int* decodeWord(int*);   // dekodovanje 

    public:

    // konstruktor
    Hamming();
    Hamming(Config,userSide);                  // kompletna inicijalizacija na osnovu informacione dužine
    // destruktor
    ~Hamming() {delete[] output; delete[] outputCopy;};

    void fillAndProcess(int*);          // napuniti frejmove bitima za slanje 
    int* getOutput() const {return outputCopy;}
    int getHammingLength() const {return codeLength;};
    void setHamming(Config simConfig, userSide externSide);
    
    // ispis podataka o Hemingovom kodu
    void printHammingInfo() const;

};

#endif