#ifndef CRC_BLOCK_H
#define CRC_BLOCK_H


#include "Polynomial.h"

class CrcBlock
{
    Polynomial poly;

    public:

    // konstruktori
	// inicijalizacija praznim blokom
    CrcBlock(): poly(-1,nullptr){}   

	// inicijalizacija bloka polinomom
    CrcBlock(const Polynomial& externPoly): poly(externPoly){}  

	// inicijalizacija bloka drugim blokom
    CrcBlock(const CrcBlock& crc): poly(crc.poly){}       


    Polynomial getCrcGenerator() const; 
	// funkcija uzima Polynomial i kopira u član "poly"
    void setCrcGenerator(const Polynomial&);    
    void setCrcGenerator(const CrcBlock& externCrc){poly = externCrc.poly;}

	// funkcija uzima informacionu sekvencu (const int*) i njenu dužinu 
	// i na izlaz šalje kodnu sekvecnu
    int* encodeWord(int, const int*);  
	// funkcija uzima sekvencu bita (const int*) određene dužine (int) 
	// i vraća flag koji govori da li sekvenca sadrži grešku
    int checkSum(int, const int*);  

    // ispis crc bloka
    void printCrcBlock() const;

};

#endif
