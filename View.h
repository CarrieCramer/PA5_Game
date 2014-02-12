#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include "Cart_Point.h"
#include "Game_Object.h"
using namespace std;

const int view_maxsize = 20;
//Max size of the grid array

class View
{
 private:

  int size;
  //Current size of the grid to be displayed

  double scale;
  //Distance represented by each cell of the grid

  Cart_Point origin;
  //Coordinates of the lower left-hand corner of the grid

  char grid[view_maxsize][view_maxsize][2];
  //Array that holds the characters that make up the display grid

  bool get_subscripts(int &ix, int &iy, Cart_Point location);
  //Calculates the column and row subscripts of the grid array that correspond to the supplied location; returns true if the subscripts are valid and prints an error message & returns false if they are invalid

 public:

  View();
  //Sets the size to 11, scale to 2, and origin to (0,0)

  void clear();
  //Sets all the cells of the grid to the default background pattern

  void plot(Game_Object *ptr);
  //Plots the pointed-to object in the proper cell of the grid; if there is already an object plotted in that cell, the characters are replaced with '*' and '' to indicate that there is more than one object in that cell

  void draw();
  //Displays the grid array

};
#endif
