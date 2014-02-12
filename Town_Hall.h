#ifndef TOWN_HALL_H
#define TOWN_HALL_H

#include <iostream>
#include <fstream>
#include "Cart_Point.h"
#include "Game_Object.h"
using namespace std;

class Model;

class Town_Hall: public Game_Object
{
 private:

  //Amount of gold currently in the town hall
  double amount;

 public:

  Town_Hall();
  //Default constructor

  Town_Hall(int in_id, Cart_Point in_loc);
  //Constructor that initializes the id number and location to the input arguments

  ~Town_Hall();
  //Prints a message when the Model class deletes a Town_Hall object
  
  void deposit_gold(double deposit_amount);
  //Adds the input amount to the gold in the Town_Hall

  bool update();
  //If the Town_Hall has gold greater than or equal to 50, it sets the state to ‘u’ for “Upgraded”, changes display_code to ‘T’, prints the message “Town_Hall (id number) has been upgraded.” and returns true. If it doesn't have enough gold or it has already been upgraded, the function returns false.

  void show_status();
  //Prints the status of the object

  void save(ofstream& file);
 //Calls the save function for Game_Object, then writes to the file the member variables declared in this class

  void restore(ifstream& file, Model& model);
  //Reads from the file into the member variables declared in this class

};

#endif
