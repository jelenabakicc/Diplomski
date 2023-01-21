#include "Polynomial.h"


Polynomial::Polynomial()
{
    polyDegree = -1;             // nepostojeći stepen polinoma
    polyCoefficients = nullptr;  // ne postoje ni koeficijenti
}

Polynomial::Polynomial(int degree, const int* coeffs)
{
    polyDegree = degree; 
    
    polyCoefficients = new int[polyDegree+1];   //alocira se memorija za koeficijente 
    
    for(int i=0;i<=polyDegree;i++) polyCoefficients[i] = coeffs[i];
}

Polynomial::Polynomial(const Polynomial& poly)  //konstruktor kopije
{
    polyDegree = poly.polyDegree;
    polyCoefficients = new int[polyDegree+1]; 

    for(int i=0;i<=polyDegree;i++) polyCoefficients[i] = poly.polyCoefficients[i];
}

Polynomial::Polynomial(Polynomial&& poly)  //konstruktor kopije
{
    polyDegree = poly.polyDegree;
    polyCoefficients = new int[polyDegree+1]; 

    for(int i=0;i<=polyDegree;i++) polyCoefficients[i] = poly.polyCoefficients[i]; 
    poly.setPolynomial(-1,nullptr);

}
void Polynomial::printPolynomial() const //ispis polinoma
{
    bool flag = true;

    cout << "Polynomial: ";
    for(int i=0;i<=polyDegree;i++)
    {
        if(polyCoefficients[i]==1) 
        {
           if(flag){ cout << "x^" << polyDegree - i; flag = false;}
           else cout << "+x^" << polyDegree - i;
        } 
        
    }
    if(flag) cout << 0;
    cout << endl;
    cout << "--------------------------------------\n";
}

int Polynomial::getPolyDegree() const
{
    return this->polyDegree; // pristup preko podrazumevanog pokazivača this (korišćenje pokazivača this u ovom primeru nije bilo neophodno)
}


int* Polynomial::getPolyCoefficients() const
{
    int* polyPtr = new int[polyDegree+1];
    for (int i=0;i<=polyDegree;i++) polyPtr[i]=polyCoefficients[i];

    return polyPtr;
}

void Polynomial::setPolynomial(int degree, int* polyPtr)
{
    
    if(polyDegree>-1)
    {    
        
        delete[] polyCoefficients;  // brišu se prethodno korišćeni koeficijenti
    }

    polyDegree = degree;   // direktan pristup privatnom članu

    if(polyDegree>-1)
    {      
    polyCoefficients = new int[polyDegree+1];  // alocira se nova memorija za koeficijente

        for (int i=0;i<=polyDegree;i++) polyCoefficients[i] = polyPtr[i];
    }
    else
        polyCoefficients = nullptr;

}

Polynomial Polynomial::operator=(const Polynomial& poly)
{
    polyDegree = poly.polyDegree;
    polyCoefficients = new int[polyDegree+1]; 

    for(int i=0;i<=polyDegree;i++) polyCoefficients[i] = poly.polyCoefficients[i];

    return *this;

}

void Polynomial::calculateReminder(Polynomial& poly)
{
    int* rem;
    rem = new int[poly.polyDegree+1];

    int* temp;                            //pomoći pokazivač koji pokazuje na tekući rezultat deljenja
    temp = new int[poly.polyDegree+1];

    for(int i=0;i<poly.polyDegree+1;i++)
        rem[i]=polyCoefficients[i];                    //ostatak pri deljenju se inicijalizuje na deljenik

    for(int j=poly.polyDegree+1;j<=polyDegree+1;j++)
    {
        for(int m=0;m<poly.polyDegree+1;m++) temp[m]=rem[m];

        if(rem[0]==0)                // ako je naveći stepen tekućeg ostatka '0' preskače se jedan stepen deljenja 
        {
            for(int m=0;m<poly.polyDegree;m++) rem[m]=temp[m+1];

        
        }
        else                    // u suprotnom se vrši XOR operacija tekućeg ostatka i deljenika
        {    
            for(int i=0;i<poly.polyDegree;i++)
                rem[i]=(temp[i+1]+poly.polyCoefficients[i+1])%2;
            
        }
        if(j!=polyDegree+1)
            rem[poly.polyDegree]=polyCoefficients[j];        //dodaje se sledeći bit deljenika
       else
            rem[poly.polyDegree]=0;
    }


    delete[] polyCoefficients; // sada je moguće izbrisati stare koeficijente da bi se upisali novi

    polyCoefficients = new int[poly.polyDegree];   // dodela memorije za nove koeficijente

    for(int m=0;m<poly.polyDegree;m++) polyCoefficients[m]=rem[m];  // kopiranje ostatka (rem) u nove koeficijente

    delete[] rem;
    delete[] temp;

    polyDegree = poly.polyDegree-1;   // novi maksimalni stepen polinoma ostatka 

}