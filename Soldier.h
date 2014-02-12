#ifndef SOLDIER_H
#define SOLDIER_H

#include <iostream>
#include "Person.h"
using namespace std;

class Model;

class Soldier: public Person
{
 private:

  int attack_strength;
  //Number of attack points delivered to the target with each "hit"

  double range;
  //The target must be within this distance to start attacking and stay within this distance to continue attacking

  Person * target;
  //Object being attacked

 public:

  Soldier();
  //Invokes Person('S'), initializes attack_strength to 2, range to 2.0, and outputs a message

  Soldier(int in_id, Cart_Point in_loc);
  //Invokes Person('S', in_id, in_loc), initializes attack_strength to 2, range to 2.0, and outputs a message

  ~Soldier();
  //Prints a message when the Model class deletes a Soldier object

  void start_attack(Person * in_target);
  //If the distance to the target is less than or equal to the range, outputs a message, saves the target pointer, and sets the state to 'a' (attack). if it is too far away, outputs a message 

  bool update();
  //Updates the Soldier according to its state

  void show_status();
  //Outputs "Soldier status: ", calls Person::show_status(), and outputs whether the object is attacking

  void save(ofstream& file);
  //Calls the save function for Person, then writes to the file the member variables declared in this class

  void restore(ifstream& file, Model& model);
  //Reads from the file into the member variables declared in this class

  void take_hit(int attack_strength, Person* attacker_ptr);
    //Tells the Soldier to attack the attacker

};

#endif
