#ifndef CRC_BLOCK_H
#define CRC_BLOCK_H


#include "Polynomial.h"

class CrcBlock
{
    Polynomial poly;

    public:

    // konstruktori
    CrcBlock(): poly(-1,nullptr){}                                       //inicijalizacija praznim blokom
    CrcBlock(const Polynomial& externPoly): poly(externPoly){}          // inicijalizacija bloka polinomom
    CrcBlock(const CrcBlock& crc): poly(crc.poly){}                     // inicijalizacija bloka drugim blokom

    Polynomial getCrcGenerator() const; 
    void setCrcGenerator(const Polynomial&);  // funkcija uzima Polynomial i kopira u član "poly"  
    void setCrcGenerator(const CrcBlock& externCrc){poly = externCrc.poly;}

    int* encodeWord(int, const int*);  // funkcija uzima informacionu sekvencu (const int*) i njenu dužinu i na izlaz šalje kodnu sekvecnu
    int checkSum(int, const int*);  // funkcija uzima sekvencu bita (const int*) određene dužine (int) i vraća flag koji govori da li sekvenca sadrži grešku

    // ispis crc bloka
    void printCrcBlock() const;

};

#endif