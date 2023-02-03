#include "CrcBlock.h"

Polynomial CrcBlock::getCrcGenerator() const
{
    return poly;
}

void CrcBlock::setCrcGenerator(const Polynomial& externPoly)
{
    int* intPtr;
    
    intPtr = externPoly.getPolyCoefficients();
    poly.setPolynomial(externPoly.getPolyDegree(),intPtr);

    delete[] intPtr;
}

int* CrcBlock::encodeWord(int infoLength,const int* infoWord)
{
    int codewordLength;
    int* codeword;

    codewordLength = infoLength+poly.getPolyDegree();

    codeword = new int[codewordLength];

	// informaciona reč se kopira na početak kodne reči 
    for(int m=0;m<infoLength;m++)  codeword[m]=infoWord[m];             

	//informacioni frejm se dopunja nulama
    for(int i=0;i<poly.getPolyDegree();i++)                            
        codeword[infoLength+i]=0;
    
	//kreira se novi objekat polinom koji predstavlja informacionu reč
    Polynomial newPoly(codewordLength-1,codeword);  
    
    newPoly.calculateReminder(poly);   // određuje se crc dodatak

    int* intPtr;
    
    intPtr = newPoly.getPolyCoefficients(); // vraća pokazivač na dinamički niz

    for(int i=0;i<=newPoly.getPolyDegree();i++)		
        codeword[infoLength+i]=intPtr[i];  // crc dodatak se lepi na kraj kodne reči              

    delete[] intPtr;

    return codeword;
}


int CrcBlock::checkSum(int codewordLength, const int codeword[])
{
    int errorFlag = 0;

	// objekat "newPoly" će se obrisati kad se završi izvršavanje funkcije,  
	// kada će se pozvati njegov destruktor koji će obrisati dinamičku memoriju 
	// dodeljenu objektu
    Polynomial newPoly(codewordLength-1,codeword);  
    newPoly.calculateReminder(poly);   // provera da li je crc dodatak ispravan
    
    int* intPtr;
    
    intPtr = newPoly.getPolyCoefficients();

    for (int i=0; i<poly.getPolyDegree(); i++)
    {
        if(intPtr[i]!=0) 
        {
            errorFlag = 1;
            break;
        }
    }

    delete[] intPtr;

    return errorFlag;
}

void CrcBlock::printCrcBlock() const
{
    cout << "CRC ";
    poly.printPolynomial();    
}