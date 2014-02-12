#ifndef MINER_H
#define MINER_H

#include <iostream>
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Person.h"
using namespace std;

class Model;

class Miner: public Person
{
 private:
  
  //Amount of gold currently being carried
  double amount;

  //A pointer to the Gold_Mine to be mined
  Gold_Mine*mine;

  //A pointer to the Town_Hall where the gold will be deposited
  Town_Hall*home;

 public:
  
  Miner();
  //Invokes Person('M'), initializes amount to 0 and mine and home pointers to NULL, outputs a message

  Miner(int in_id, Cart_Point in_loc);
  //Invokes Person('M',in_id,in_loc), initializes amount to 0 and mine and home pointers to 0, outputs a message
 
  ~Miner();
  //Prints a message when the Model class deletes a Miner object

  void show_status();
  //Outputs "Miner status:", calls Person::show_status(), and displays info about the Miner-specific states of inbound, outbound, getting gold, and depositing gold

  bool update();
 //Returns true when the state is changed and updates the status of the object on each time unit

 void start_mining(Gold_Mine* in_mine, Town_Hall* in_home);
 //Tells the miner to start mining, which includes moving gold from the mine to home (Gold_Mine and Town_Hall objects)

 void save(ofstream& file);
 //Calls the save function for Person, then writes to the file the member variables declared in this class

 void restore(ifstream& file, Model& model);
  //Reads from the file into the member variables declared in this class

 void take_hit(int attack_strength, Person* attacker_ptr);
   //Tells the Miner to run away from the attacker
  
};

#endif
