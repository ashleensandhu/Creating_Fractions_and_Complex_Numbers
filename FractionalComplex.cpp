#include <iostream>
#include "FractionalComplex.h"
#include<cmath>
using namespace std;
// Ashleen Sandhu, CS132, Spring
// Programming Assignment Fractions, 05/04/2023
//
/* This program's behavior is to create a fractional complex
and then can create a default fraction, or let's the user create a fraction.
It can then add, subtract, reduce, multiply, check equality, and has it's own 
operators beyond that. 
*/

//default constructor
FractionalComplex::FractionalComplex()
{
   topLeft=0;
   botLeft=1;
   topRight=0;
   botRight=1;
}
//constructor that allows user to enter numerators for fractions
FractionalComplex::FractionalComplex(int x, int y)
{
   topLeft=x;
   botLeft=1;
   topRight=y;
   botRight=1;
}
//constructor that allows user to choose all four numbers 
//then reduces to smallest form
FractionalComplex::FractionalComplex(int a, int b, int c, int d)
{  

   topLeft=a;
   botLeft=b;
   topRight=c;
   botRight=d;
   
   if(b==0) 
   {
      topLeft=0;
      botLeft=1;
   }
   if(d==0) 
   {
      topRight=0;
      botRight=1;
   }
   
   Reduce();
}
/********************* METHODS**************************/
//prints fractional complex
void FractionalComplex::printme() const
{
   cout << "[(" << topLeft << "/" << botLeft << ")+" << "(" << topRight << "/" <<botRight << ")i]" << endl;
}

/*********************PRIVATE METHODS*******************/
//method reduces fraction
void FractionalComplex::Reduce()
{
   //first gets greates common denomenator
   gcd1 = GCD(topLeft, botLeft);
   
   gcd2 = GCD(topRight, botRight);
   
   //changes negetive sign to the correct place if needed
   if(botLeft<0) 
   {
      topLeft = topLeft*(-1);
      botLeft = botLeft*(-1);
   }
   if(botRight<0)
   {
      topRight = topRight*(-1);
      botRight = botRight*(-1);
   }
   
   //dividing by greates common denomenator
    topLeft = topLeft/gcd1;
    botLeft = botLeft/gcd1;
    topRight = topRight/gcd2;
    botRight = botRight/gcd2;  
}
//calculates greates common denomenator
int FractionalComplex::GCD(int x, int y)
{
   x=abs(x);
   y=abs(y);
   //if y==0 return x else run the method again
   return y==0 ? x: GCD(y, x%y);
}

//returns the numeric value of the fraction as double
double FractionalComplex::length() const
{
   double frac1= topLeft*1.0/botLeft;
   double frac2 = topRight*1.0/botRight;

   return sqrt((frac1*frac1)+(frac2*frac2));
}
/*********************OPERATORS*******************/
//allows you to add two fractions together
const FractionalComplex FractionalComplex::operator+(const FractionalComplex RHS)
{
   FractionalComplex z;
   //z is the new fraction that will be returned
   z.topLeft =((this->topLeft*RHS.botLeft)+(this->botLeft*RHS.topLeft));
   z.botLeft =(this->botLeft*RHS.botLeft);
   
   z.topRight =((this->topRight*RHS.botRight)+(this->botRight*RHS.topRight));
   z.botRight =(this->botRight*RHS.botRight);
   
   z.Reduce();//reducing it before it's returned
   
   return z;
}
//subtracts two fractions
const FractionalComplex FractionalComplex::operator-(const FractionalComplex RHS)
{
   FractionalComplex x;
   //x is the new fractional complex that will be returned
   x.topLeft = ((this->topLeft*RHS.botLeft)-(this->botLeft*RHS.topLeft));
   x.botLeft = (this->botLeft*RHS.botLeft);
   
   x.topRight=((this->topRight*RHS.botRight)-(this->botRight*RHS.topRight));
   x.botRight=(this->botRight*RHS.botRight);
   
   x.Reduce();//reducing it before it's returned
   
   return x;
}
//checks equality of two fractions
const bool FractionalComplex::operator==(const FractionalComplex RHS) 
{
  //making sure each value is an exact mathc to the other
   if(this->topLeft==RHS.topLeft && this->botLeft==RHS.botLeft && this->topRight==RHS.topRight && this->botRight==RHS.botRight)
   return true;  
   else return false;
}
//uses the length to see which one is smaller
const bool FractionalComplex::operator<(const FractionalComplex RHS)
{
   return (length() < RHS.length());
}

//uses the length to see which one is bigger
const bool FractionalComplex::operator>(const FractionalComplex RHS)
{
   return (length() > RHS.length());
}

//multiplys two fractional complexes
const FractionalComplex FractionalComplex::operator*(const FractionalComplex RHS)
{
   //the first fraction that is created when multiplying
   FractionalComplex frontEnd;
   frontEnd.topLeft= this->topLeft * RHS.topLeft;
   frontEnd.botLeft = this->botLeft * RHS.botLeft;
   frontEnd.topRight= this->topLeft * RHS.topRight;
   frontEnd.botRight = this->botLeft * RHS.botRight;
   
   //the second fraction that is created when multiplying
   FractionalComplex backEnd;
   backEnd.topLeft= (-1) * this->topRight * RHS.topRight;
   backEnd.botLeft = this->botRight * RHS.botRight;
   backEnd.topRight= this->topRight * RHS.topLeft;
   backEnd.botRight = this->botRight * RHS.botLeft;
   
   //add the two fractions together to create the final one
   FractionalComplex final = frontEnd+backEnd;
   
   return final;
   
}

//allows you to multiply a fractional complex with a number
const FractionalComplex FractionalComplex::operator*(int RHS)
{
   FractionalComplex y;
   //y is the fractional complex that will be returned
   y.topLeft = this->topLeft * RHS;
   y.botLeft = this->botLeft;
   y.topRight = this->topRight * RHS;
   y.botRight = this->botRight;
   y.Reduce();//reducing before its returned
   
   return y;
}
//prefix addition of fractional complex
FractionalComplex FractionalComplex::operator++(int x) //PREFIX
{
   FractionalComplex copy = *this; //i'm making a copy of myself
   topLeft = topLeft+botLeft; 
   topRight = topRight+botRight; 
   return copy;//sending you my old version then next time you try to print me I will be updated
}

//postfix addition of fractional complex
FractionalComplex FractionalComplex::operator++() //POSTFIX
{
   topLeft = topLeft+botLeft; 
   topRight = topRight+botRight;   
   return *this;
}

/*********************OUTSIDE-OPERATORS*******************/
// >> operator, no longer need printme method
std::ostream& operator<<(std::ostream& o, const FractionalComplex RHS)
{
   o << "[(" << RHS.topLeft << "/" << RHS.botLeft << ")+" << "(" << RHS.topRight << "/" <<RHS.botRight << ")i]";   //main will determine when it needz and endl;
   return o;
}
