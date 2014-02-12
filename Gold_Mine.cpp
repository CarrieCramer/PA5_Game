#include <iostream>
#include "Gold_Mine.h"
#include "Model.h"
using namespace std;

Gold_Mine::Gold_Mine():Game_Object('G')
{
  //Amount of gold currently in the mine
  amount = 100;

  cout << "    Gold_Mine default constructed." << endl;
}

Gold_Mine::Gold_Mine(int in_id, Cart_Point in_loc):Game_Object('G',in_id,in_loc)
//Constructor that initializes the id number and location to the input values
{
  //Amount of gold currently in the mine
  amount = 100;

  cout << "    Gold_Mine constructed.\n";
}

Gold_Mine::~Gold_Mine()
//Prints a message when the Model class deletes a Gold_Mine object
{
  cout << "    Gold_Mine destructed.\n";
}

bool Gold_Mine::is_empty()
//Returns true if this Gold_Mine contains 0 gold, otherwise returns false
{
  if (amount == 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}
  
double Gold_Mine::dig_gold(double amount_to_dig)
//If the amount of gold in the mine is greater than or equal to amount_to_dig, it subtracts amount_to_dig from Gold_Mine’s amount and returns amount_to_dig. Otherwise, it returns the Gold_Mine’s current amount, and amount is set to 0. Has a default input argument.
{
  if (amount >= amount_to_dig)
    {
      amount = amount - amount_to_dig;
      return amount_to_dig;
    }
  else
    {
      double currentAmount = amount;
      amount = 0;
      return currentAmount;
    }
}

bool Gold_Mine::update()
//If the gold mine is empty, it sets the state to ‘e’ for “empty”, changes display_code to ‘g’, prints the message “Gold_Mine (id number) has been depleted.” and lastly, returns true (only at the time when the Gold_Mine becomes empty). Returns false if it is not depleted or if it has been depleted and update is called again.
{
  if ( (this->is_empty()) && (state != 'e') )
    {
      state = 'e';
      display_code = 'g';
      cout << "Gold_Mine " << Game_Object::get_id() << " has been depleted.\n";
      return true;
    }
  else 
    {
      return false;
    }
} 

void Gold_Mine::show_status()
//Prints out the status of the object
{
  cout << "Gold Mine status: ";

  Game_Object::show_status();

  cout << "Contains " << amount << ".\n";
}

double Gold_Mine::get_gold_amount()
//Returns the amount of gold currently in the Gold_Mine
{
  return amount;
}

void Gold_Mine::save(ofstream& file)
//Calls the save function for Game_Object, then writes to the file the member variables declared in this class
{
  Game_Object::save(file);

  file << amount << endl;
}

void Gold_Mine::restore(ifstream& file, Model& model)
//Reads from the file into the member variables declared in this class
{
  Game_Object::restore(file, model);

  //Sets amount
  double output;
  file >> output;
  amount = output;
}
