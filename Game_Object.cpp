#include <fstream>
#include "Game_Object.h"
#include "Cart_Point.h"
#include "Model.h"

Game_Object::Game_Object()
//Initializes display_code to " ", state to 's', id_num to 0, and outputs a message
 {
   display_code = ' ';
   state = 's';
   id_num = 0;

   cout << "    Game_Object default constructed.\n";
 }

Game_Object::Game_Object(char in_code)
//Initializes display_code, sets remaining initial values, outputs a message
 {
  display_code = in_code;
  
  if(in_code == 't')
    {
      state = 'o';
    }
  else
    {
      state = 's';
    }
  
  id_num = 1;

  cout << "    Game_Object constructed.\n";
    
 }
  
Game_Object::Game_Object(char in_code, int in_id, Cart_Point in_loc)
//Initializes display_code, id_num, & location, sets remaining initial values and outputs a message
{
  display_code = in_code;
  id_num = in_id;
  location.x = in_loc.x;
  location.y = in_loc.y;

  if(in_code == 't')
    {
      state = 'o';
    }
  else if (in_code == 'G')
    {
      state == 'f';
    }
  else
    {
      state = 's';
    }
  
 

  cout << "    Game_Object constructed.\n";
}
 
Game_Object::~Game_Object()
//Prints a message when the Model class deletes a Game_Object 
{
  cout << "    Game_Object destructed.\n";
}

Cart_Point Game_Object::get_location()
//Returns a Cart_Point object with the coordinates of the object
{
  Cart_Point p1(location.x, location.y);
  return p1;
}

int Game_Object::get_id()
//Returns the id_num of the object
{
  return id_num;
}

int Game_Object::get_display_code()
//Returns the display_code of the object
{
  return display_code;
}

void Game_Object::set_id_num(int id)
//Sets id_num
{
  id_num = id;
}

void Game_Object::set_display_code(char code)
//Sets display_code
{
  display_code = code;
}

void Game_Object::show_status()
//Outputs the display_code, id_num, and location contained in the class
{
  cout << display_code << id_num << " at location " << location << " ";
}

void Game_Object::drawself(char * ptr)
 //Puts the display_code at the character pointed to by ptr, and the ASCII character for the id_num in the next character
{
  char idChar = id_num + 48;
  *ptr = display_code;
  *(ptr+1) = idChar;
  
}

bool Game_Object::is_alive()
//Always returns true
{
  return true;
}


void Game_Object::save(ofstream& file)
{
  file << display_code  << endl << id_num << endl << location.x << endl << location.y << endl << state << endl;
}

void Game_Object::restore(ifstream& file, Model& model)
//Reads from the file into the member variables declared in this class
{
  for (int i = 1; i <=5; i++)
    {
      if ((i == 1)||(i == 2))
	{
	  //Do nothing with display_code and id_num, they are already set in Model::restore
	  char output;
	  file >> output;
	}
      else if (i == 3)
	{
	  //Set location.x
	  double output;
	  file >> output;
	  location.x = output;
	}
      else if (i == 4)
	{
	  //Set location.y
	  double output;
	  file >> output;
	  location.y = output;
	}
      else if (i == 5)
	{
	  //Set state
	  char output;
	  file >> output;
	  state = output;
	}
      
    }
}

