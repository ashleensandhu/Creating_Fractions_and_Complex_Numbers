#ifndef FRACTIONALCOMPLEX__H
#define FRACTIONALCOMPLEX__H

#include<iostream>
//Fractional Complex class
class FractionalComplex
{
   public:
      //costructors
      FractionalComplex();
      FractionalComplex(int, int);
      FractionalComplex(int, int, int, int);
      //functions
      void printme() const;
      //operators
      const FractionalComplex operator+(const FractionalComplex);
      const FractionalComplex operator-(const FractionalComplex);
      const bool operator==(const FractionalComplex);
      const bool operator<(const FractionalComplex);
      const bool operator>(const FractionalComplex);
      const FractionalComplex operator*(const FractionalComplex);
      const FractionalComplex operator*(int);
      
      FractionalComplex operator++(int);
      FractionalComplex operator++(); 
      
      //friends
      friend std::ostream& operator<<(std::ostream&, const FractionalComplex);
      
   private:
      int topLeft;
      int botLeft;
      int topRight;
      int botRight;
      int gcd1;
      int gcd2;
      //functions
      void Reduce();
      int GCD(int, int);//greatest common denominator
      double length() const;
      
};
//operator
//needs to be outside of the class becase the LHS is stream not Fractional COmplex
std::ostream& operator<<(std::ostream&, const FractionalComplex);

#endif