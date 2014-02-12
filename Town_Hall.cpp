#include <iostream>
#include "Town_Hall.h"
#include "Game_Object.h"
#include "Model.h"
using namespace std;

Town_Hall::Town_Hall():Game_Object('t')
//Default constructor
{
  //Amount of gold currently in the town hall
  amount = 0;

  cout << "    Town_Hall default constructed.\n"; 
 }

Town_Hall::Town_Hall(int in_id, Cart_Point in_loc):Game_Object('t',in_id,in_loc)
//Constructor that initializes the id number and location to the input arguments
{
  //Amount of gold currently in the town hall
  amount = 0;

  cout << "    Town_Hall constructed.\n";
  
}

Town_Hall::~Town_Hall()
//Prints a message when the Model class deletes a Town_Hall object
{
  cout << "    Town_Hall destructed.\n";
}

void Town_Hall::deposit_gold(double deposit_amount)
//Adds the input amount to the gold in the Town_Hall
{
  amount = amount + deposit_amount;
}

bool Town_Hall::update()
//If the Town_Hall has gold greater than or equal to 50, it sets the state to ‘u’ for “Upgraded”, changes display_code to ‘T’, prints the message “Town_Hall (id number) has been upgraded.” and returns true. If it doesn't have enough gold or it has already been upgraded, the function returns false.
{
  if ( (amount >= 50) && (state != 'u'))
    {
      Game_Object::state = 'u';
      display_code = 'T';
      cout << display_code << Game_Object::get_id() << " has been upgraded." << endl;
      return true;
    }
  else
    {
      return false;
    }
}

void Town_Hall::show_status()
//Prints the status of the object
{
  cout << "Town Hall status: ";

  Game_Object::show_status();

  cout << "Contains " << amount << " of gold.";

  if (state == 'u')
    {
      cout << "   Upgraded" << endl;
    }
  else
    {
      cout << "   Not yet upgraded" << endl;
    }
}

void Town_Hall::save(ofstream& file)
//Calls the save function for Game_Object, then writes to the file the member variables declared in this class
{
  Game_Object::save(file);

  file << amount << endl;
}

void Town_Hall::restore(ifstream& file, Model& model)
//Reads from the file into the member variables declared in this class
{
  Game_Object::restore(file, model);

  //Sets amount
  double output;
  file >> output;
  amount = output;
}
