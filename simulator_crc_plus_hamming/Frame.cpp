
#include "Frame.h"


Frame::Frame():crc()                    //inicijalizacija praznim blokom
{
    numFrames = 0;
    payloadSize = 0;
    overheadSize = 0;
    numDetectedFailures = -1;
    output = nullptr;
    outputCopy = nullptr;

}    


Frame::Frame(const CrcBlock& externCrc, const Config& myConfig, userSide externSide): crc(externCrc)                  //kompletna inicijalizacija 
{
    numFrames = myConfig.numFrames;
    payloadSize = myConfig.payloadSize;
    numDetectedFailures = -1;

    overheadSize = myConfig.overheadSize;
    
    outputCopy = new int[numFrames*(payloadSize+overheadSize)];
    output = new int[numFrames*(payloadSize+overheadSize)];

    side = externSide;

}  

void Frame::setFrame(const CrcBlock& externCrc,const Config& myConfig, userSide externSide)
{
    numFrames = myConfig.numFrames;
    payloadSize = myConfig.payloadSize;
    numDetectedFailures = -1;
    
    crc.setCrcGenerator(externCrc);

    overheadSize = myConfig.overheadSize;

    if(output != nullptr) {delete[] output; delete[] outputCopy;}
    
    side = externSide; 

    if(side == transmit)
    {
        output = new int[numFrames*(payloadSize+overheadSize)];
        outputCopy = new int[numFrames*(payloadSize+overheadSize)];
    }
    else
    {
        output = new int[numFrames*payloadSize];
        outputCopy = new int[numFrames*payloadSize];
    }
     

}


void Frame::fillAndProcess(int* inputStream)
{

    if(side==transmit)  // frejmovima se pre kopiranja u objektu dodaje CRC zaglavlje
    {
        int* tempInputFrame;
        int* tempOutputFrame;

        //tempOutputFrame = new int[payloadSize+overheadSize];

        for(int i=0;i<numFrames;i++)
        {

            tempInputFrame = new int[payloadSize];

            for(int j=0;j<payloadSize;j++)  tempInputFrame[j]=inputStream[i*payloadSize+j];

            tempOutputFrame = crc.encodeWord(payloadSize,tempInputFrame);

            for(int j=0;j<payloadSize+overheadSize;j++)  output[i*(payloadSize+overheadSize)+j]=tempOutputFrame[j];    // kopiranje privremenog frejma u izlazni niz frejmova

            delete[] tempOutputFrame;
            delete[] tempInputFrame;

        }


        for (int i=0;i<(payloadSize+overheadSize)*numFrames;i++) outputCopy[i] = output[i];  // pravi se kopija izlaznog niza

        
   }
   else 
   {    
        checkFrames(inputStream); // vrši se provera CRC dodatka

        int counter = 0;
        for (int i=0;i<(payloadSize+overheadSize)*numFrames;i++) 
        { 
            if (i%(payloadSize+overheadSize)<payloadSize) output[counter++]=inputStream[i];
        }

        for (int i=0;i<payloadSize*numFrames;i++) outputCopy[i] = output[i];  // pravi se kopija izlaznog niza

   }

}

void Frame::checkFrames(int* inputStream) // funkcija ne alocira novu memoriju (sva dinamički dodeljena memorija se briše u okviru funkcije)
{
    numDetectedFailures = 0;
    int errorFlag;
    int* tempFrame;


    for (int i=0;i<numFrames;i++)
    {
        tempFrame = new int[payloadSize+overheadSize];

        for (int j=0;j<payloadSize+overheadSize;j++) tempFrame[j] = inputStream[i*(payloadSize+overheadSize)+j];

        errorFlag = crc.checkSum(payloadSize+overheadSize,tempFrame);
        
        delete[] tempFrame;

        numDetectedFailures += errorFlag;

        if(errorFlag==1)   // obeležavanje pogrešno primljenih frejmova (detektovane greške se koduju numeričkom vrednošću "2")
        {
            for (int j=0;j<payloadSize+overheadSize;j++) inputStream[i*(payloadSize+overheadSize)+j]=2;
        } 
    }

}  
void Frame::printFrameInfo() const
{
    cout << "--------------------------------------\n";
    cout << "Num. of transmitted frames: " << numFrames << endl;
    cout << "--------------------------------------\n";
    cout << "Payload size: " << payloadSize << endl;
    cout << "--------------------------------------\n";
    cout << "Num. of detected failures: " << numDetectedFailures << endl;

    crc.printCrcBlock();

}
