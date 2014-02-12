#ifndef CART_VECTOR_H
#define CART_VECTOR_H

#include <iostream>
using namespace std;

class Cart_Vector
{
 public:
  
  //x and y displacement values of the vector
  double x;
  double y;
  
  //Default constructor
  Cart_Vector();

  //Constructor that sets x and y to the user input
  Cart_Vector(double inputx, double inputy);

  //Nonmember overloaded stream output operator: produces output formatted as (x,y)
  friend ostream &operator<<(ostream &out, Cart_Vector &v1);

  //Nonmember overloaded multiplication operator: returns a Cart_Vector object with x = v1*d and y = v1*d
  friend Cart_Vector operator*(Cart_Vector &v1, double d);
  
  //Nonmember overloaded division operator: returns a Cart_Vector object with x = v1/d and y = v1/d
  friend Cart_Vector operator/(Cart_Vector &v1, double d);
  
};



#endif
