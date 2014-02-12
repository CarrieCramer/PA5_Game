#include <iostream>
#include "Cart_Vector.h"
using namespace std;

//Default constructor
Cart_Vector :: Cart_Vector()
{
  x = 0.0;
  y = 0.0;
}

//Constructor that sets x and y to the user input
Cart_Vector :: Cart_Vector(double inputx, double inputy)
{
  x = inputx;
  y = inputy;
}

//Nonmember overloaded stream output operator: produces output formatted as (x,y)
ostream &operator<<(ostream &out, Cart_Vector &v1)
{
  out << "<" << v1.x << "," << v1.y << ">";
  return out;
}

//Nonmember overloaded multiplication operator: returns a Cart_Vector object with x = v1*d and y = v1*d
Cart_Vector operator*(Cart_Vector &v1, double d)
{
  double xNew = v1.x * d;
  double yNew = v1.y * d;
  Cart_Vector*ptrV2 = new Cart_Vector(xNew,yNew);
  Cart_Vector v2 = *ptrV2;
  return v2;
}

//Nonmember overloaded division operator: returns a Cart_Vector object with x = v1/d and y = v1/d
Cart_Vector operator/(Cart_Vector &v1, double d)
{
  double xNew = v1.x / d;
  double yNew = v1.y / d;
  Cart_Vector*ptrV2 = new Cart_Vector(xNew,yNew);
  Cart_Vector v2 = *ptrV2;
  return v2;
}
