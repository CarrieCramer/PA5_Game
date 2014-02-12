#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <list>
#include "Game_Object.h"
#include "Person.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "View.h"
#include "Inspector.h"

using namespace std;

class Model
{
 private:

  //Simulation time
  int time;

  //Linked list that stores the pointers to all Game_Objects
  list<Game_Object*> object_ptrs;

  //Linked list that stores the pointers to all Game_Objects. If an object dies, it will be removed from this list.
  list<Game_Object*> active_ptrs;

  //Linked list that stores the pointers to all Person objects
  list<Person*> person_ptrs;

  //Linked list that stores the pointers to all Gold_Mine objects
  list<Gold_Mine*> mine_ptrs;

  //Linked list that stores the pointers to all Town_Hall objects
  list<Town_Hall*> hall_ptrs;

  //******************DELETE WHEN DONE**********************************
  /* //Arrays of pointers and a variable for the number in each array */
  /* Game_Object * object_ptrs[10]; */
  /* int num_objects; */
  
  /* Person * person_ptrs[10]; */
  /* int num_persons; */

  /* Gold_Mine * mine_ptrs[10]; */
  /* int num_mines; */

  /* Town_Hall * hall_ptrs[10]; */
  /* int num_halls; */
  //********************************************************************

 public:

  Model();
  //Initializes the time to 0, creates objects on the heap, stores pointers to them, and prints a message

  ~Model();
  //Deletes each object and outputs a message

  Person * get_Person_ptr(int id);
  //Searches the person_ptrs array for an object matching the supplied id, returns the pointer if found or 0 if not

  Gold_Mine * get_Gold_Mine_ptr(int id);
  //Searches the mine_ptrs array for an object matching the supplied id, returns the pointer if found or 0 if not

  Town_Hall * get_Town_Hall_ptr(int id);
  //Searches the hall_ptrs array for an object matching the supplied id, returns the pointer if found or 0 if not

  bool update();
  //Increments the time, iterates through the object_ptrs array and calls update() for each object, returns true if any of the update() calls returns true

  void display(View &view);
  //Outputs the time and generates the view display for all of the Game_Objects

  void show_status();
  //Outputs the status of all of the Game_Objects by calling their show_status()function

  void handle_new_command(View &view);
  //Called when the n TYPE ID X Y command is entered as an input, creates a new object with the input specifications and adds its pointer to the appropriate lists depending on its type

  list<Gold_Mine*> get_Gold_Mine_list();
  //Returns a copy of the mine pointers list

  void save(ofstream& file);
  //Writes the current time and catalog information into the save file, calls each object's save function

  void restore(ifstream& file);
  //Deletes all existing Game_Objects and empties all lists, restores the time, Game_Objects, and lists

};

#endif 
