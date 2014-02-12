#ifndef CART_POINT_H
#define CART_POINT_H

#include <iostream>
#include "Cart_Vector.h"
using namespace std;

class Cart_Point
{
public:
  
  //x and y values of a cartesian point
  double x;
  double y;

  //Default constructor
  Cart_Point();

  //Constructor that sets the x and y values to the user input
  Cart_Point(double inputx, double inputy);

  //Nonmember overloaded stream output operator: produces output formatted as (x,y)
  friend ostream &operator<<(ostream &out, Cart_Point &p1);

  //Nonmember overloaded addition operator: returns a Cart_Point object
  friend Cart_Point operator+(Cart_Point &p1, Cart_Vector &v1);

  //Nonmember overloaded subtraction operator: returns a Cart_Point object
  friend Cart_Vector operator-(Cart_Point &p1, Cart_Point &p2);
  
};

//Non-member function that returns the distance between two Cart_Point objects
double cart_distance(Cart_Point p1, Cart_Point p2);

#endif

