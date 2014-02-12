#include <iostream>
#include "Cart_Point.h"
#include <cmath>
using namespace std;


//Default constructor
Cart_Point :: Cart_Point()
  {
    x = 0.0;
    y = 0.0;
  }

//Constructor that sets the x and y values to the user input
Cart_Point :: Cart_Point(double inputx, double inputy)
  {
    x = inputx;
    y = inputy;
  }

double cart_distance(Cart_Point p1, Cart_Point p2)
//Returns the distance between two Cart_Point objects
{
  //Distance formula
  double dist = sqrt(pow((p2.x-p1.x),2)+pow((p2.y-p1.y),2));
  return dist;
}

//Nonmember overloaded stream output operator: produces output formatted as (x,y)
ostream &operator<<(ostream &out, Cart_Point &p1)
{
  out << "(" << p1.x << "," << p1.y << ")";
  return out;
}

//Nonmember overloaded addition operator: returns a Cart_Point object
 Cart_Point operator+(Cart_Point &p1, Cart_Vector &v1)
  {
    double xNew = p1.x + v1.x;
    double yNew = p1.y + v1.y;
    Cart_Point*ptrP2 = new Cart_Point(xNew,yNew);
    Cart_Point p2 = *ptrP2;
    return p2;
  }

//Nonmember overloaded subtraction operator: returns a Cart_Point object
 Cart_Vector operator-(Cart_Point &p1, Cart_Point &p2)
  {
    double xNew = p1.x - p2.x;
    double yNew = p1.y - p2.y;
    Cart_Vector*ptrV2 = new Cart_Vector(xNew,yNew);
    Cart_Vector v2 = *ptrV2;
    return v2;
  }


