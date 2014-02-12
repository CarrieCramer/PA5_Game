#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <list>
#include "Gold_Mine.h"
#include "Cart_Point.h"
#include "Person.h"

class Model;

class Inspector: public Person
{
 private:

  //Linked list that stores the pointers to the Gold_Mines that haven't been inspected yet
  list<Gold_Mine*>mines_to_inspect;

  //Linked list used as a LIFO stack for the mines that have been inspected on the outbound portion of the trip
  list<Gold_Mine*>mines_inspected;

  //Linked list that stores the amounts that were in each mine on the outbound trip
  list<double>mine_amounts;

  //Starting location of the current inspection trip
  Cart_Point starting_location;

  //Iterator that points to the mine currently being inspected
  list<Gold_Mine*>::iterator current_mine;

 public:

  Inspector();
  //Invokes Person('I'), outputs a message

  Inspector(int in_id, Cart_Point in_loc);
  //Invokes Person('I', in_id, in_loc), outputs a message

  ~Inspector();
  //Prints a message when the model class deletes an Inspector object

  void show_status();
  //Outputs "Inspector status:", calls Person::show_status(), and displays info about the Miner-specific states of moving outbound, reporting outbound, moving inbound, reporting inbound

  bool update();
  //Returns true when the Inspector arrives at a destination

  void find_closest_mine();
  //Loops through mines_to_inspect to find the mine closest to the Inspector, sets the current_mine iterator to point to this mine

  void start_inspecting(Model &model);
  //Tells the Inspector to start inspecting

  void report_outbound();
  //Performs the Inspector's actions during an outbound report

  void report_inbound();
  //Performs the Inspector's actions during an inbound report

  void save(ofstream& file);
 //Calls the save function for Person, then writes to the file the member variables declared in this class

  void restore(ifstream& file, Model& model);
  //Reads from the file into the member variables declared in this class
};


#endif
