#ifndef SOURCE_SINK_H
#define SOURCE_SINK_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include<iostream>

#include "Config.h"


using namespace std;



class SourceSink
{
    int sourceStreamSize;
    double transProb01;  // verovatnoće prelaza 
    double transProb10;
    int* output;  // izvor baferiše niz koji je poslao zbog vođenja statistike
    int* outputCopy;  

    public:
    // konstruktori
    SourceSink() {sourceStreamSize = 0; transProb01 = 0.5; transProb10 = 0.5; output =nullptr;}                           
    SourceSink(const Config& myConfig): sourceStreamSize{myConfig.sourceStreamSize},  transProb01{myConfig.transProb01}, transProb10{myConfig.transProb10} 
                {output = new int[sourceStreamSize]; outputCopy = new int[sourceStreamSize];};

    ~SourceSink() {delete[] output; delete[] outputCopy;}  //briše se baferisani niz
	
    void setSourceSize(int size) {sourceStreamSize = size; output = new int[sourceStreamSize]; outputCopy = new int[sourceStreamSize];}; 
    void setTarnsProbs(double p01, double p10) {transProb01 = p01; transProb10 = p10;}; 

    int* getOutput(){return outputCopy;}
    void generateStream();
    void calculateErrors(const Config&, int*);


};

#endif