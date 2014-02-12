#include "View.h"
#include "Cart_Point.h"

View::View()
//Sets the size to 11, scale to 2, and origin to (0,0)
{
  size = 11;
  scale = 2;
  origin.x = 0;
  origin.y = 0;
}

bool View::get_subscripts(int &ix, int &iy, Cart_Point location)
//Calculates the column and row subscripts of the grid array that correspond to the supplied location; returns true if the subscripts are valid and prints an error message & returns false if they are invalid
{
  //Assign the subscripts to the reference parameters
  iy = (location.x-origin.x)/scale + 1;
  ix = (location.y-origin.y)/scale + 1;
  
  //Return true if the subscripts are within the size of the grid being displayed
  if ((ix <= size) && (iy <= size))
    {
      return true;
    } 
  else
    {
      //If the subscripts are invalid, print error message and return false
      cout << "An object is outside the display\n";
      return false;
    }
}

void View::clear()
//Sets all the cells of the grid to the default background pattern
{
  //Store dot & space characters for the blank grid
  for (int i = 1; i <= size; i++)   //Iterates over the rows
    {
      for (int j = 1; j <= size; j++)   //Iterates over the columns
	{
	  grid[i][j][0] = '.';
	  grid[i][j][1] = ' ';
	}
     
    } 
}
void View::plot(Game_Object *ptr)
//Plots the pointed-to object in the proper cell of the grid; if there is already an object plotted in that cell, the characters are replaced with '*' and ' ' to indicate that there is more than one object in that cell
{
  //Calculate the object's location subscripts 
  int ix;
  int iy;
  Cart_Point loc = ptr->get_location();
  get_subscripts(ix,iy,loc);

  //Check if an object already exists in the location before adding the display_code and id_num to the grid array 
  if ((grid[ix][iy][0] != '.') && (grid[ix][iy][1] != ' '))
    {
      grid[ix][iy][0] = '*';
      grid[ix][iy][1] = ' ';
    }
  else
    {
     ptr->drawself(grid[ix][iy]);
    }


}

void View::draw()
//Displays the grid array
{
 //Store y-axis characters
  grid[0][0][0] = ' ';
  grid[1][0][0] = '0';
  grid[2][0][0] = ' ';
  grid[3][0][0] = '4';
  grid[4][0][0] = ' ';
  grid[5][0][0] = '8';
  grid[6][0][0] = ' ';
  grid[7][0][0] = '1';
  grid[8][0][0] = ' ';
  grid[9][0][0] = '1';
  grid[10][0][0] = ' ';
  grid[11][0][0] = '2';
  grid[0][0][1] = ' ';
  grid[1][0][1] = ' ';
  grid[2][0][1] = ' ';
  grid[3][0][1] = ' ';
  grid[4][0][1] = ' ';
  grid[5][0][1] = ' ';
  grid[6][0][1] = ' ';
  grid[7][0][1] = '2';
  grid[8][0][1] = ' ';
  grid[9][0][1] = '6';
  grid[10][0][1] = ' ';
  grid[11][0][1] = '0';

  
  //Store x-axis characters
  grid[0][1][0] = '0';
  grid[0][2][0] = ' ';
  grid[0][3][0] = '4';
  grid[0][4][0] = ' ';
  grid[0][5][0] = '8';
  grid[0][6][0] = ' ';
  grid[0][7][0] = '1';
  grid[0][8][0] = ' ';
  grid[0][9][0] = '1';
  grid[0][10][0] = ' ';
  grid[0][11][0] = '2';
  grid[0][1][1] = ' ';
  grid[0][2][1] = ' ';
  grid[0][3][1] = ' ';
  grid[0][4][1] = ' ';
  grid[0][5][1] = ' ';
  grid[0][6][1] = ' ';
  grid[0][7][1] = '2';
  grid[0][8][1] = ' ';
  grid[0][9][1] = '6';
  grid[0][10][1] = ' ';
  grid[0][11][1] = '0';
  
for (int i = size; i >= 0; i--)
    {
      for (int j = 0; j <= size; j++)
	{
	  cout << grid[i][j][0] << grid[i][j][1];
	}
      cout << endl;
    }
}
