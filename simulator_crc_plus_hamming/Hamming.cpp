#include "Hamming.h"

Hamming::Hamming()
{
    infoLength = 1;
    codeLength = 1;
    numFrames = -1;
    output = nullptr;
    outputCopy = nullptr;
    side = transmit;
}

Hamming::Hamming(Config simConfig, userSide externSide)
{
    infoLength = simConfig.overheadSize+simConfig.payloadSize;
    codeLength = calculateCodeLength();
    numFrames = simConfig.numFrames;
    side = externSide;

    if(side==transmit)
    {
        output = new int[codeLength*numFrames];
        outputCopy = new int[codeLength*numFrames];
    }
    else
    {
        output = new int[infoLength*numFrames];   
        outputCopy = new int[infoLength*numFrames];   
    }
    
}

void Hamming::setHamming(Config simConfig, userSide externSide)
{
    infoLength = simConfig.overheadSize+simConfig.payloadSize;
    codeLength = calculateCodeLength();
    numFrames = simConfig.numFrames;
    
    if(output != nullptr) { delete[] output; delete[] outputCopy;}

    side = externSide;

     if(side==transmit)
    {
        output = new int[codeLength*numFrames];
        outputCopy = new int[codeLength*numFrames];
    }
    else
    {
        output = new int[infoLength*numFrames];   
        outputCopy = new int[infoLength*numFrames];   
    }
    
}

int Hamming::calculateCodeLength()
{
    int redundaceLength = 0;

     while((redundaceLength+infoLength+1)>(pow(2,redundaceLength)))           
        redundaceLength++;

    return redundaceLength+infoLength;   
}


int* Hamming::encodeWord(int* infoWord)
{
    int* codeword;
    codeword = new int[codeLength]; 

    int counterRedundancy = 0;
    int counterInfo = 0;
    int parityPosition;

    for(int i=0;i<codeLength;i++)
    {

        if(i+1==pow(2,counterRedundancy))
        {
            counterRedundancy++;
            codeword[i] = 0;
        }
         else
         {
            codeword[i] = infoWord[counterInfo++];
         }

    }

    for(int i=0;i<counterRedundancy;i++)
    {
        parityPosition = pow(2,i)-1;
        codeword[parityPosition] = calculateParity(codeword, parityPosition);

    }

    return codeword;
}

int Hamming::calculateParity(int* codeword, int parityPosition)
{
    int parity = 0;
    int blockLength = parityPosition + 1; 
    int counter = 0;

    while (counter+parityPosition<codeLength)
    {
        
        parity += codeword[parityPosition+counter];
        counter++;
        
        if((counter % blockLength)==0) counter += blockLength;

    }

    return parity%2;   
}

int* Hamming::decodeWord(int receivedWord[])
{
    int* decodedWord;
    decodedWord = new int[infoLength]; 

    int errorPosition = 0;

    int counterRedundancy = 0;
    int counterInfo = 0;


    int parityPosition;
    int correctionBit;
 

    for(int i=0;i<codeLength-infoLength;i++)
    {
        parityPosition = pow(2,i)-1;
        errorPosition += pow(2,i)*calculateParity(receivedWord, parityPosition); 
    }

    for(int i=0;i<codeLength;i++)
    {
        if(i==errorPosition-1) correctionBit = 1;
        else correctionBit = 0;

        if(i+1!=pow(2,counterRedundancy)) decodedWord[counterInfo++] = (receivedWord[i]+correctionBit)%2;
        else counterRedundancy++;

    }

    return decodedWord;  
}


void Hamming::fillAndProcess(int* inputStream)
{
        
        int* tempInfoFrame;
        int* tempCodedFrame;
        
        if(side==transmit)
        {

            for(int i=0;i<numFrames;i++)
            {
                tempInfoFrame = new int[infoLength];

                for(int j=0;j<infoLength;j++) tempInfoFrame[j]=inputStream[i*infoLength+j];

                tempCodedFrame = encodeWord(tempInfoFrame);

                delete[] tempInfoFrame;  

                for(int j=0;j<codeLength;j++) output[i*codeLength+j]=tempCodedFrame[j];  
                
                delete[] tempCodedFrame; 

            }

            for(int i=0;i<numFrames*codeLength;i++) outputCopy[i] = output[i];  // pravljenje kopije za izlaz

        }
        else
        {

            for(int i=0;i<numFrames;i++)
            {

                tempCodedFrame = new int[codeLength];

                for(int j=0;j<codeLength;j++) tempCodedFrame[j]=inputStream[i*codeLength+j];

                tempInfoFrame = decodeWord(tempCodedFrame);

                delete[] tempCodedFrame; 

                for(int j=0;j<infoLength;j++) output[i*infoLength+j]=tempInfoFrame[j];  

                delete[] tempInfoFrame;  

            }

            for(int i=0;i<numFrames*infoLength;i++) outputCopy[i] = output[i];  // pravljenje kopije za izlaz

        } 

}

 void Hamming::printHammingInfo() const
    {
    cout<< "Hemingov kod: " <<"(" << codeLength << "," << infoLength << ")" << endl;
    cout<< "------------------------------------------------------------"<< endl;
    
    }

