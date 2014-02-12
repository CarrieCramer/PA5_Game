#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <fstream>
#include "Game_Object.h"
#include "Cart_Vector.h"
#include "Cart_Point.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"

using namespace std;

class Model;

class Person: public Game_Object
{
 public:

  Person();
  //Initializes the speed to 5 and outputs a message

  Person(char in_code);
  //Invokes Game_Object(in_code) and initializes speed to 5, outputs a message

  Person(char in_code, int in_id, Cart_Point in_loc);
  //Invokes Game_Object(in_code, in_id, in_loc) and initializes the speed to 5, outputs a message

  virtual ~Person();
  //Prints a message when the Model class deletes a Person object

  virtual void start_moving(Cart_Point dest);
  //Tells the person to start moving

  void stop();
  //Tells the person to stop moving or mining by setting the state to stopped

  void show_status();
  //Calls Game_Object::show_status, outputs the information in this class for the moving and stopped state (speed, destination, delta)

 virtual void start_mining(Gold_Mine* in_mine, Town_Hall* in_home);
 //Just prints the message "Sorry, I can't work a mine"

 virtual void start_inspecting(Model &model);
 //Just prints the message "Sorry, I can't inspect"

 bool is_alive();
 //Returns true if the state is not 'x', false if it is 'x'

 virtual void take_hit(int attack_strength, Person* attacker_ptr);
 //Subtracts the attack_strength from the health. If the new value of health is less than or equal to zero, prints a message and sets the state to 'x'. Otherwise, prints a different message and leaves the state unchanged.

 virtual void start_attack(Person * target);
 //Outputs a message "I can't attack." 

 void save(ofstream& file);
 //Calls the save function for Game_Object, then writes to the file the member variables declared in this class

 void restore(ifstream& file, Model& model);
  //Reads from the file into the member variables declared in this class

 protected:

  bool update_location();
  //Updates the object's location while it is moving

  void setup_destination(Cart_Point dest);
  //Sets up the object to start moving to a destination
 
 private:

  double speed;
  //The speed that the object travels (distance per update time unit)

  Cart_Point destination;
  //This object's current destination coordinates

  Cart_Vector delta;
  //x and y amounts that the object will move during each time unit

  int health;
  //The health of the character
  
};

#endif
