#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<iostream>
using namespace std;

class Polynomial
{
    int polyDegree;    // maksimalni stepen polinoma
    int* polyCoefficients;  // vektor koeficijenata 

    public:

    // konstruktori
    Polynomial();    //inicijlizacija praznim polinomom
    Polynomial(const int degree, const int* coeffs);     // inicijalizacija vektorom 
														 // koeficijenata
    Polynomial(const Polynomial& poly);   // inicijalizacija drugim polinomom
    Polynomial(Polynomial&& poly);   // inicijalizacija drugim polinomom

    // destruktor
    ~Polynomial() {delete[] polyCoefficients;};  

    Polynomial operator=(const Polynomial& poly);

    // pristup privatnim članovima preko javnih metoda
    int getPolyDegree() const;
    int* getPolyCoefficients() const;

    void setPolynomial(int, int*);

    // ispis polinoma
    void printPolynomial() const;

    // ostatak deljenja dva polinoma se smešta u polinom deljenika, dok se kao argument 
	// uzima polinom delioca
    void calculateReminder(Polynomial& poly);

};

#endif
