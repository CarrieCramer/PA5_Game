#ifndef GOLD_MINE_H
#define GOLD_MINE_H

#include <iostream>
#include <fstream>
#include "Cart_Point.h"
#include "Game_Object.h"
using namespace std;

class Model;

class Gold_Mine: public Game_Object
{
 private:

  //Amount of gold currently in the mine
  double amount;

 public:
  
  Gold_Mine();
  //Default constructor
  
  Gold_Mine(int in_id, Cart_Point in_loc);
  //Constructor that initializes the id number and location to the input values
  
  ~Gold_Mine();
  //Prints a message when the Model class deletes a Gold_Mine object

  bool is_empty();
  //Returns true if this Gold_Mine contains 0 gold, otherwise returns false

  double dig_gold(double amount_to_dig = 35.0);
  //If the amount of gold in the mine is greater than or equal to amount_to_dig, it subtracts amount_to_dig from Gold_Mine’s amount and returns amount_to_dig. If the amount of gold in the mine is less, it returns the Gold_Mine’s current amount, and amount is set to 0. Has a default iput argument.

  bool update();
  //If the gold mine is empty, it sets the state to ‘e’ for “empty”, changes display_code to ‘g’, prints the message “Gold_Mine (id number) has been depleted.” and lastly, returns true (only at the time when the Gold_Mine becomes empty). Returns false if it is not depleted or if it has been depleted and update is called again.
 
  void show_status();
  //Prints out the status of the object

  double get_gold_amount();
  //Returns the amount of gold currently in the Gold_Mine
  
  void save(ofstream& file);
 //Calls the save function for Game_Object, then writes to the file the member variables declared in this class

  void restore(ifstream& file, Model& model);
  //Reads from the file into the member variables declared in this class
};


#endif
